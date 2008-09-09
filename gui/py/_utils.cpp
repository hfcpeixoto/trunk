#include<yade/extra/Shop.hpp>
#include<boost/python.hpp>
#include<yade/core/MetaBody.hpp>
#include<yade/core/Omega.hpp>
#include<yade/pkg-common/Sphere.hpp>
#include<yade/pkg-dem/SpheresContactGeometry.hpp>
#include<yade/extra/Brefcom.hpp>
#include<cmath>
using namespace boost::python;

#ifdef LOG4CXX
	log4cxx::LoggerPtr logger=log4cxx::Logger::getLogger("yade.utils");
#endif

python::tuple vec2tuple(const Vector3r& v){return boost::python::make_tuple(v[0],v[1],v[2]);}
Vector3r tuple2vec(const python::tuple& t){return Vector3r(extract<double>(t[0])(),extract<double>(t[1])(),extract<double>(t[2])());}
bool isInBB(Vector3r p, Vector3r bbMin, Vector3r bbMax){return p[0]>bbMin[0] && p[0]<bbMax[0] && p[1]>bbMin[1] && p[1]<bbMax[1] && p[2]>bbMin[2] && p[2]<bbMax[2];}

/* \todo implement groupMask */
python::tuple aabbExtrema(){
	Real inf=std::numeric_limits<Real>::infinity();
	Vector3r minimum(inf,inf,inf),maximum(-inf,-inf,-inf);
	FOREACH(const shared_ptr<Body>& b, *Omega::instance().getRootBody()->bodies){
		shared_ptr<Sphere> s=dynamic_pointer_cast<Sphere>(b->geometricalModel); if(!s) continue;
		Vector3r rrr(s->radius,s->radius,s->radius);
		minimum=componentMinVector(minimum,b->physicalParameters->se3.position-rrr);
		maximum=componentMaxVector(maximum,b->physicalParameters->se3.position+rrr);
	}
	return python::make_tuple(vec2tuple(minimum),vec2tuple(maximum));
}

python::tuple negPosExtremeIds(int axis, Real distFactor=1.1){
	python::tuple extrema=aabbExtrema();
	Real minCoord=extract<double>(extrema[0][axis])(),maxCoord=extract<double>(extrema[1][axis])();
	python::list minIds,maxIds;
	FOREACH(const shared_ptr<Body>& b, *Omega::instance().getRootBody()->bodies){
		shared_ptr<Sphere> s=dynamic_pointer_cast<Sphere>(b->geometricalModel); if(!s) continue;
		if(b->physicalParameters->se3.position[axis]-s->radius*distFactor<=minCoord) minIds.append(b->getId());
		if(b->physicalParameters->se3.position[axis]+s->radius*distFactor>=maxCoord) maxIds.append(b->getId());
	}
	return python::make_tuple(minIds,maxIds);
}
BOOST_PYTHON_FUNCTION_OVERLOADS(negPosExtremeIds_overloads,negPosExtremeIds,1,2);

python::tuple coordsAndDisplacements(int axis,python::tuple AABB=python::tuple()){
	Vector3r bbMin(Vector3r::ZERO), bbMax(Vector3r::ZERO); bool useBB=python::len(AABB)>0;
	if(useBB){bbMin=tuple2vec(extract<python::tuple>(AABB[0])());bbMax=tuple2vec(extract<python::tuple>(AABB[1])());}
	python::list retCoord,retDispl;
	FOREACH(const shared_ptr<Body>&b, *Omega::instance().getRootBody()->bodies){
		if(useBB && !isInBB(b->physicalParameters->se3.position,bbMin,bbMax)) continue;
		retCoord.append(b->physicalParameters->se3.position[axis]);
		retDispl.append(b->physicalParameters->se3.position[axis]-b->physicalParameters->refSe3.position[axis]);
	}
	return python::make_tuple(retCoord,retDispl);
}
BOOST_PYTHON_FUNCTION_OVERLOADS(coordsAndDisplacements_overloads,coordsAndDisplacements,1,2);

void setRefSe3(){
	FOREACH(const shared_ptr<Body>& b, *Omega::instance().getRootBody()->bodies){
		b->physicalParameters->refSe3.position=b->physicalParameters->se3.position;
		b->physicalParameters->refSe3.orientation=b->physicalParameters->se3.orientation;
	}
}

Real PWaveTimeStep(){return Shop::PWaveTimeStep();};

Real elasticEnergyInAABB(python::tuple AABB){
	Vector3r bbMin=tuple2vec(extract<python::tuple>(AABB[0])()), bbMax=tuple2vec(extract<python::tuple>(AABB[1])());
	shared_ptr<MetaBody> rb=Omega::instance().getRootBody();
	Real E=0;
	FOREACH(const shared_ptr<Interaction>&i, *rb->transientInteractions){
		if(!i->interactionPhysics) continue;
		//FIXME: dynamic_pointer_cast instead of static should be used here, but the downcast fails for reasons that are not know :-(
		shared_ptr<BrefcomContact> bc=static_pointer_cast<BrefcomContact>(i->interactionPhysics); if(!bc) continue;
		const shared_ptr<Body>& b1=Body::byId(i->getId1(),rb), b2=Body::byId(i->getId2(),rb);
		bool isIn1=isInBB(b1->physicalParameters->se3.position,bbMin,bbMax), isIn2=isInBB(b2->physicalParameters->se3.position,bbMin,bbMax);
		if(!isIn1 && !isIn2) continue;
		LOG_DEBUG("Interaction #"<<i->getId1()<<"--#"<<i->getId2());
		//cerr<<"Interaction #"<<i->getId1()<<"--#"<<i->getId2()<<endl;
		Real weight=1.;
		if((!isIn1 && isIn2) || (isIn1 && !isIn2)){
			//shared_ptr<Body> bIn=isIn1?b1:b2, bOut=isIn2?b2:b1;
			Vector3r vIn=(isIn1?b1:b2)->physicalParameters->se3.position, vOut=(isIn2?b1:b2)->physicalParameters->se3.position;
			#define _WEIGHT_COMPONENT(axis) if(vOut[axis]<bbMin[axis]) weight=min(weight,abs((vOut[axis]-bbMin[axis])/(vOut[axis]-vIn[axis]))); else if(vOut[axis]>bbMax[axis]) weight=min(weight,abs((vOut[axis]-bbMax[axis])/(vOut[axis]-vIn[axis])));
			_WEIGHT_COMPONENT(0); _WEIGHT_COMPONENT(1); _WEIGHT_COMPONENT(2);
			assert(weight>=0 && weight<=1);
			//cerr<<"Interaction crosses AABB boundary, weight is "<<weight<<endl;
			//LOG_DEBUG("Interaction crosses AABB boundary, weight is "<<weight);
		} else {assert(isIn1 && isIn2); /* cerr<<"Interaction inside, weight is "<<weight<<endl;*/ /*LOG_DEBUG("Interaction inside, weight is "<<weight);*/}
		E+=weight*(.5*bc->E*bc->crossSection*pow(bc->epsN,2)+.5*bc->G*bc->crossSection*pow(bc->epsT.Length(),2));
		//TRVAR5(bc->crossSection,bc->E,bc->G,bc->epsN,bc->epsT.Length());;
		//cerr<<bc->crossSection<<","<<bc->E<<","<<bc->G<<","<<bc->epsN<<","<<bc->epsT.Length()<<endl;
	}
	return E;
}


/* return histogram ([bin1Min,bin2Min,…],[value1,value2,…]) from projections of interactions
 * to the plane perpendicular to axis∈[0,1,2]; the number of bins can be specified and they cover
 * the range (0,π), since interactions are bidirecional, hence periodically the same on (π,2π).
 *
 * Only contacts using SpheresContactGeometry are considered.
 * Both bodies must be in the mask (except if mask is 0, when all bodies are considered)
 * If the projection is shorter than minProjLen, it is skipped.
 *
 * If both bodies are _outside_ the aabb (if specified), the interaction is skipped.
 *
 */
python::tuple interactionAnglesHistogram(int axis, int mask=0, size_t bins=20, python::tuple aabb=python::tuple(), Real minProjLen=1e-6){
	if(axis<0||axis>2) throw invalid_argument("Axis must be from {0,1,2}=x,y,z.");
	Vector3r bbMin(Vector3r::ZERO), bbMax(Vector3r::ZERO); bool useBB=python::len(aabb)>0; if(useBB){bbMin=tuple2vec(extract<python::tuple>(aabb[0])());bbMax=tuple2vec(extract<python::tuple>(aabb[1])());}
	Real binStep=Mathr::PI/bins; int axis2=(axis+1)%3, axis3=(axis+2)%3;
	vector<Real> cummProj(bins,0.);
	shared_ptr<MetaBody> rb=Omega::instance().getRootBody();
	FOREACH(const shared_ptr<Interaction>& i, *rb->transientInteractions){
		if(!i->isReal) continue;
		const shared_ptr<Body>& b1=Body::byId(i->getId1(),rb), b2=Body::byId(i->getId2(),rb);
		if(!b1->maskOk(mask) || !b2->maskOk(mask)) continue;
		if(useBB && !isInBB(b1->physicalParameters->se3.position,bbMin,bbMax) && !isInBB(b2->physicalParameters->se3.position,bbMin,bbMax)) continue;
		shared_ptr<SpheresContactGeometry> scg=dynamic_pointer_cast<SpheresContactGeometry>(i->interactionGeometry); if(!scg) continue;
		Vector3r n(scg->normal); n[axis]=0.; Real nLen=n.Length();
		if(nLen<minProjLen) continue; // this interaction is (almost) exactly parallel to our axis; skip that one
		Real theta=acos(n[axis2]/nLen)*(n[axis3]>0?1:-1); if(theta<0) theta+=Mathr::PI;
		int binNo=theta/binStep;
		cummProj[binNo]+=nLen;
	}
	python::list val,binMid;
	for(size_t i=0; i<(size_t)bins; i++){ val.append(cummProj[i]); binMid.append(i*binStep);}
	return python::make_tuple(binMid,val);
}
BOOST_PYTHON_FUNCTION_OVERLOADS(interactionAnglesHistogram_overloads,interactionAnglesHistogram,1,4);


BOOST_PYTHON_MODULE(_utils){
	def("PWaveTimeStep",PWaveTimeStep);
	def("aabbExtrema",aabbExtrema);
	def("negPosExtremeIds",negPosExtremeIds,negPosExtremeIds_overloads(args("axis","distFactor")));
	def("coordsAndDisplacements",coordsAndDisplacements,coordsAndDisplacements_overloads(args("AABB")));
	def("setRefSe3",setRefSe3);
	def("interactionAnglesHistogram",interactionAnglesHistogram,interactionAnglesHistogram_overloads(args("axis","mask","bins","aabb")));
	def("elasticEnergy",elasticEnergyInAABB);
}


