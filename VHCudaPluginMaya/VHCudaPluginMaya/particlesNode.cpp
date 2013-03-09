#include "particlesNode.h"

MTypeId     particlesNode::id( 0x800128 );

MObject     particlesNode::aEmitters;
MObject     particlesNode::aFluid;

MObject     particlesNode::aInTime;
MObject     particlesNode::aOutTime;

MObject     particlesNode::aMaxParts;

MObject		particlesNode::aStartFrame;
MObject		particlesNode::aSubsteps;

MObject		particlesNode::aLife;
MObject		particlesNode::aLifeVar;

MObject		particlesNode::aVelDamp;
MObject		particlesNode::aGravityStrength;
MObject		particlesNode::aGravityX;
MObject		particlesNode::aGravityY;
MObject		particlesNode::aGravityZ;
MObject		particlesNode::aGravityDir;

MObject		particlesNode::aFluidStrength;

MObject		particlesNode::aNoiseAmp;
MObject		particlesNode::aNoiseOffsetX;
MObject		particlesNode::aNoiseOffsetY;
MObject		particlesNode::aNoiseOffsetZ;
MObject		particlesNode::aNoiseOffset;

MObject		particlesNode::aNoiseFreq;
MObject		particlesNode::aNoiseOct;
MObject		particlesNode::aNoiseLacun;

MObject		particlesNode::aPreview;
MObject		particlesNode::aShadedMode;
MObject		particlesNode::aSpritePath;

MObject		particlesNode::aLightPosX;
MObject		particlesNode::aLightPosY;
MObject		particlesNode::aLightPosZ;
MObject		particlesNode::aLightPos;

MObject		particlesNode::aLightTargetX;
MObject		particlesNode::aLightTargetY;
MObject		particlesNode::aLightTargetZ;
MObject		particlesNode::aLightTarget;

MObject		particlesNode::aLightColorR;
MObject		particlesNode::aLightColorG;
MObject		particlesNode::aLightColorB;
MObject		particlesNode::aLightColor;

MObject		particlesNode::aColorAttenuationR;
MObject		particlesNode::aColorAttenuationG;
MObject		particlesNode::aColorAttenuationB;
MObject		particlesNode::aColorAttenuation;
MObject		particlesNode::aShadowAlpha;

MObject		particlesNode::aOpaScale;
MObject		particlesNode::aPointSize;

MObject		particlesNode::aStartColorR;
MObject		particlesNode::aStartColorG;
MObject		particlesNode::aStartColorB;
MObject		particlesNode::aStartColor;

MObject		particlesNode::aEndColorR;
MObject		particlesNode::aEndColorG;
MObject		particlesNode::aEndColorB;
MObject		particlesNode::aEndColor;

//
void* particlesNode::creator()
{
	return new particlesNode();
}

void particlesNode::draw( M3dView & view, const MDagPath & path, 
						M3dView::DisplayStyle style,
						M3dView::DisplayStatus status ){



	view.beginGL(); 

	glPushAttrib(GL_CURRENT_BIT|GL_VIEWPORT_BIT|GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDisable(GL_DEPTH_TEST);

	MObject thisNode = thisMObject();

	MPlug prevPlug( thisNode, aPreview );
	prevPlug.getValue(particlesSystem->preview );


	if(particlesSystem->preview) {

		//if ( ( style == M3dView::kFlatShaded ) ||  ( style == M3dView::kGouraudShaded ) ) {  


				MPlug shadedModePlug( thisNode, aShadedMode );
				int shadedMode;
				shadedModePlug.getValue(shadedMode );

				MDataHandle spritePathHandle;

				MPlug spritePathPlug( thisNode, aSpritePath );
				spritePathPlug.getValue(spritePathHandle );
				
				MString spritePath = spritePathHandle.asString();
				MString oldSprite = particlesSystem->pRend->spritePath;

				if (spritePath != oldSprite) {
					//particlesSystem->lockOpenGLContext();
					particlesSystem->pRend->loadSprite((char*)(spritePath.asChar()));
					//particlesSystem->unlockOpenGLContext();
					particlesSystem->pRend->spritePath = (char*)(spritePath.asChar());
				}


				if(shadedMode) {
					particlesSystem->pRend->displayMode = 3;
					particlesSystem->pRend->blendingMode = 1;
					particlesSystem->pRend->sortParts = 1;
				} else {
					particlesSystem->pRend->displayMode = 0;
					particlesSystem->pRend->blendingMode = 0;
					particlesSystem->pRend->sortParts = 0;
				}

				particlesSystem->pRend->nSlices = 128;
				particlesSystem->pRend->resMul = 1;

			    MPlug lightPosXPlug( thisNode, aLightPosX );
				float lightPosX;
				lightPosXPlug.getValue(lightPosX);

				MPlug lightPosYPlug( thisNode, aLightPosY );
				float lightPosY;
				lightPosYPlug.getValue(lightPosY);

				MPlug lightPosZPlug( thisNode, aLightPosZ );
				float lightPosZ;
				lightPosZPlug.getValue(lightPosZ);
				particlesSystem->pRend->lightPos = vec3f(lightPosX,lightPosY,lightPosZ);


				MPlug lightTargetXPlug( thisNode, aLightTargetX );
				float lightTargetX;
				lightTargetXPlug.getValue(lightTargetX);

				MPlug lightTargetYPlug( thisNode, aLightTargetY );
				float lightTargetY;
				lightTargetYPlug.getValue(lightTargetY);

				MPlug lightTargetZPlug( thisNode, aLightTargetZ );
				float lightTargetZ;
				lightTargetZPlug.getValue(lightTargetZ);

				particlesSystem->pRend->lightTarget = vec3f(lightTargetX,lightTargetY,lightTargetZ);

				MPlug lightColorRPlug( thisNode, aLightColorR );
				float lightColR;
				lightColorRPlug.getValue(lightColR);

				MPlug lightColorGPlug( thisNode, aLightColorG );
				float lightColG;
				lightColorGPlug.getValue(lightColG);

				MPlug lightColorBPlug( thisNode, aLightColorB );
				float lightColB;
				lightColorRPlug.getValue(lightColB);

				particlesSystem->pRend->lightColor = vec3f(lightColR, lightColG, lightColB);

				MPlug colorAttRPlug( thisNode, aColorAttenuationR );
				float colorAttR;
				colorAttRPlug.getValue(colorAttR);

				MPlug colorAttGPlug( thisNode, aColorAttenuationG );
				float colorAttG;
				colorAttGPlug.getValue(colorAttG);

				MPlug colorAttBPlug( thisNode, aColorAttenuationB );
				float colorAttB;
				colorAttBPlug.getValue(colorAttB);
				particlesSystem->pRend->colorAttenuation = vec3f(colorAttR, colorAttG, colorAttB);

				MPlug shadowAlphaPlug( thisNode, aShadowAlpha );
				shadowAlphaPlug.getValue(particlesSystem->pRend->shadowAlpha);

				MPlug opaScalePlug( thisNode, aOpaScale );
				opaScalePlug.getValue(particlesSystem->opacity);

				MPlug pointSizePlug( thisNode, aPointSize );
				pointSizePlug.getValue(particlesSystem->pRend->pointSize);
				//particlesSystem->pRend->pointSize = 0.03

				MPlug startColorRPlug( thisNode, aStartColorR );
				float startColR;
				startColorRPlug.getValue(startColR);

				MPlug startColorGPlug( thisNode, aStartColorG);
				float startColG;
				startColorGPlug.getValue(startColG);

				MPlug startColorBPlug( thisNode, aStartColorB );
				float startColB;
				startColorBPlug.getValue(startColB);

				particlesSystem->startColor = cu::make_float3(startColR,startColG,startColB);

				MPlug endColorRPlug( thisNode, aEndColorR );
				float endColR;
				endColorRPlug.getValue(endColR);

				MPlug endColorGPlug( thisNode, aEndColorG);
				float endColG;
				endColorGPlug.getValue(endColG);

				MPlug endColorBPlug( thisNode, aEndColorB );
				float endColB;
				endColorBPlug.getValue(endColB);

				particlesSystem->endColor = cu::make_float3(endColR,endColG,endColB);
		
				particlesSystem->draw();

			//}
	}

	glPopAttrib();

	view.endGL();


}

//
MStatus particlesNode::initialize()
{

	MFnUnitAttribute	uAttr;
	MFnNumericAttribute nAttr;
	MFnTypedAttribute	tAttr;
	MFnEnumAttribute	eAttr;
	MFnMessageAttribute	mAttr;
	MStatus				stat;

	aEmitters = mAttr.create("emitters","ems",&stat);
	CHECK_MSTATUS(stat);
	mAttr.setArray(true);
	stat = addAttribute(aEmitters);

	aFluid = mAttr.create("fluid", "fluid", &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aFluid);

	aInTime =  uAttr.create( "inTime", "t", MFnUnitAttribute::kTime, 0.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aInTime);

	aOutTime =  uAttr.create( "outTime", "ot", MFnUnitAttribute::kTime, 0.0, &stat);
	CHECK_MSTATUS(stat);
	uAttr.setWritable(false);
	stat = addAttribute(aOutTime);

	aMaxParts =  nAttr.create( "maxParts", "mparts", MFnNumericData::kInt, 2000000, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(false);
	stat = addAttribute(aMaxParts);

	aStartFrame =  nAttr.create( "startFrame", "sf", MFnNumericData::kInt, 2, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aStartFrame);

	aSubsteps = nAttr.create("substeps", "step", MFnNumericData::kInt, 1, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aSubsteps);


	aLife = nAttr.create("life", "li", MFnNumericData::kFloat, 4.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aLife);

	aLifeVar = nAttr.create("lifeVar", "lv", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aLifeVar);

	aVelDamp = nAttr.create("velDamp", "vd", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aVelDamp);

	aGravityStrength = nAttr.create("gravityStrength", "gs", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aGravityStrength);

	aGravityX = nAttr.create("gravityX", "grx", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aGravityX);

	aGravityY = nAttr.create("gravityY", "gry", MFnNumericData::kFloat, -1.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aGravityY);

	aGravityZ = nAttr.create("gravityZ", "grz", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aGravityZ);

	aGravityDir = nAttr.create("gravityDir", "gd", aGravityX, aGravityY, aGravityZ, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	nAttr.setDefault(0,-1,0);
	stat = addAttribute(aGravityDir);

	aFluidStrength = nAttr.create("fluidStrength", "fs", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aFluidStrength);

	aNoiseAmp = nAttr.create("noiseAmp", "nam", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aNoiseAmp);

	aNoiseOffsetX = nAttr.create("noiseOffsetX", "nox", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aNoiseOffsetX);

	aNoiseOffsetY = nAttr.create("noiseOffsetY", "noy", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aNoiseOffsetY);

	aNoiseOffsetZ = nAttr.create("noiseOffsetZ", "noz", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aNoiseOffsetZ);

	aNoiseOffset = nAttr.create("noiseOffset", "nof", aNoiseOffsetX, aNoiseOffsetY, aNoiseOffsetZ, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aNoiseOffset);

	aNoiseFreq = nAttr.create("noiseFreq", "nfr", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aNoiseFreq);

	aNoiseOct = nAttr.create("noiseOct", "noc", MFnNumericData::kInt, 1.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aNoiseOct);

	aNoiseLacun = nAttr.create("noiseLacun", "nlc", MFnNumericData::kFloat, 2.0, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	stat = addAttribute(aNoiseLacun);


	aPreview = nAttr.create("preview", "prv", MFnNumericData::kBoolean, 1, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aPreview);

	aShadedMode = nAttr.create("shadedMode", "shmo", MFnNumericData::kBoolean, 0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aShadedMode);

	MFnStringData                         fnStringData;
    MObject                               defaultPath;
	defaultPath = fnStringData.create("C:/pictures/centerGradient.tif");

	aSpritePath = tAttr.create( "spritePath", "spat", MFnData::kString, defaultPath, &stat );
	CHECK_MSTATUS(stat);
	stat = addAttribute(aSpritePath);

		aLightPosX = nAttr.create("lightPosX", "lipx", MFnNumericData::kFloat, 10.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightPosX);

	aLightPosY = nAttr.create("lightPosY", "lipy", MFnNumericData::kFloat, 10.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightPosY);

	aLightPosZ = nAttr.create("lightPosZ", "lipz", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightPosZ);

	aLightPos = nAttr.create("lightPos", "lipos", aLightPosX, aLightPosY, aLightPosZ, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	nAttr.setDefault(10.0,10.0,0.0);
	stat = addAttribute(aLightPos);

	aLightTargetX = nAttr.create("lightTargetX", "ltpx", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightTargetX);

	aLightTargetY = nAttr.create("lightTargetY", "ltpy", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightTargetY);

	aLightTargetZ = nAttr.create("lightTargetZ", "ltpz", MFnNumericData::kFloat, 0.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightTargetZ);

	aLightTarget = nAttr.create("lightTarget", "ltpos", aLightTargetX, aLightTargetY, aLightTargetZ, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
	nAttr.setDefault(0.0,0.0,0.0);
	stat = addAttribute(aLightTarget);

	
	aLightColorR = nAttr.create("lightColorR", "lcr", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightColorR);

	aLightColorG = nAttr.create("lightColorG", "lcg", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightColorG);

	aLightColorB = nAttr.create("lightColorB", "lcb", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aLightColorB);

	aLightColor = nAttr.create("lightColor", "lcol", aLightColorR, aLightColorG, aLightColorB, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
    nAttr.setUsedAsColor(true);
	stat = addAttribute(aLightColor);

	aColorAttenuationR = nAttr.create("colorAttenuationR", "car", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aColorAttenuationR);

	aColorAttenuationG = nAttr.create("colorAttenuationG", "cag", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aColorAttenuationG);

	aColorAttenuationB = nAttr.create("colorAttenuationB", "cab", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aColorAttenuationB);

	aColorAttenuation = nAttr.create("colorAttenuation", "colatt", aColorAttenuationR, aColorAttenuationG, aColorAttenuationB, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
    nAttr.setUsedAsColor(true);
	stat = addAttribute(aColorAttenuation);

	aShadowAlpha = nAttr.create("shadowAlpha", "sha", MFnNumericData::kFloat, 0.3, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	stat = addAttribute(aShadowAlpha);

	aOpaScale = nAttr.create("opaScale", "opa", MFnNumericData::kFloat, 0.05, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	stat = addAttribute(aOpaScale);

	aPointSize = nAttr.create("pointSize", "pze", MFnNumericData::kFloat, 0.03, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aPointSize);

	aStartColorR = nAttr.create("startColorR", "scr", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aStartColorR);

	aStartColorG = nAttr.create("startColorG", "scg", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aStartColorG);

	aStartColorB = nAttr.create("startColorB", "scb", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aStartColorB);

	aStartColor = nAttr.create("startColor", "scol", aStartColorR, aStartColorG, aStartColorB, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
    nAttr.setUsedAsColor(true);
	stat = addAttribute(aStartColor);

	aEndColorR = nAttr.create("endColorR", "ecr", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aEndColorR);

	aEndColorG = nAttr.create("endColorG", "ecg", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aEndColorG);

	aEndColorB = nAttr.create("endColorB", "ecb", MFnNumericData::kFloat, 1.0, &stat);
	CHECK_MSTATUS(stat);
	stat = addAttribute(aEndColorB);

	aEndColor = nAttr.create("endColor", "ecol", aEndColorR, aEndColorG, aEndColorB, &stat);
	CHECK_MSTATUS(stat);
	nAttr.setKeyable(true);
    nAttr.setUsedAsColor(true);
	stat = addAttribute(aEndColor);

	


	stat = attributeAffects(aInTime, aOutTime);

	return MS::kSuccess;
} 


particlesNode::particlesNode() {

	currentMayaFluidName = "";
	solverTime = 0.0;

	particlesSystem = new VHParticlesSystem();

}


particlesNode::~particlesNode() {


	delete particlesSystem;

}


MStatus particlesNode::compute (const MPlug& plug, MDataBlock& data) {

	MStatus returnStatus;

	 if(plug == aOutTime) {

		MDataHandle inTimeHandle = data.inputValue (aInTime, &returnStatus);
		CHECK_MSTATUS( returnStatus );

		MTime currentTime(inTimeHandle.asTime());
		currentTime.setUnit(MTime::uiUnit());

		int currentFrame = (int)currentTime.value();

		MDataHandle startFrameHandle = data.inputValue (aStartFrame, &returnStatus);
		CHECK_MSTATUS( returnStatus );
		int startFrame = startFrameHandle.asInt();

		MDataHandle substepsHandle = data.inputValue (aSubsteps, &returnStatus);
		CHECK_MSTATUS( returnStatus );
		int substeps = substepsHandle.asInt();


		if(MTime::uiUnit() == MTime::kFilm) {
			particlesSystem->dt = 1.0/(24.0*substeps);
		} else if(MTime::uiUnit() == MTime::kPALFrame) {
			particlesSystem->dt = 1.0/(25.0*substeps);
		} else if(MTime::uiUnit() == MTime::kNTSCFrame) {
			particlesSystem->dt = 1.0/(30.0*substeps);
		} else if(MTime::uiUnit() == MTime::kNTSCField) {
			particlesSystem->dt = 1.0/(60.0*substeps);
		}


		MDataHandle inPreviewHandle = data.inputValue (aPreview, &returnStatus);
		CHECK_MSTATUS( returnStatus );
		particlesSystem->preview = inPreviewHandle.asBool();


		if (currentFrame < startFrame) {

			particlesSystem->resetParticles();

		} else if (currentFrame == startFrame){

			MDataHandle maxPartsHandle = data.inputValue (aMaxParts, &returnStatus);
			CHECK_MSTATUS( returnStatus );

				int maxParts = maxPartsHandle.asInt();
				if (particlesSystem->nParts!=maxParts)
					particlesSystem->changeMaxParts(maxParts,1);

		} else {

			MDataHandle lifeHandle = data.inputValue (aLife, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			particlesSystem->partsLife = lifeHandle.asFloat();

			MDataHandle lifeVarHandle = data.inputValue (aLifeVar, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			particlesSystem->partsLifeVar = lifeVarHandle.asFloat();

			MDataHandle velDampHandle = data.inputValue (aVelDamp, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			//particlesSystem->velDamp = velDampHandle.asFloat();
			((DampingForce*)(particlesSystem->leadsForces[0]))->strength = velDampHandle.asFloat();

			MDataHandle gravityStrengthHandle = data.inputValue (aGravityStrength, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			//particlesSystem->gravityStrength = gravityStrengthHandle.asFloat();
			((GravityForce*)(particlesSystem->leadsForces[1]))->strength = gravityStrengthHandle.asFloat();

			MDataHandle gravityXHandle = data.inputValue (aGravityX, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			float gravityX = gravityXHandle.asFloat();

			MDataHandle gravityYHandle = data.inputValue (aGravityY, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			float gravityY = gravityYHandle.asFloat();

			MDataHandle gravityZHandle = data.inputValue (aGravityZ, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			float gravityZ = gravityZHandle.asFloat();

			//particlesSystem->gravityDir = cu::make_float3(gravityX,gravityY,gravityZ);
			((GravityForce*)(particlesSystem->leadsForces[1]))->gravityDir = cu::make_float3(gravityX,gravityY,gravityZ);

			MDataHandle fluidStrengthHandle = data.inputValue (aFluidStrength, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			//particlesSystem->fluidStrength = fluidStrengthHandle.asFloat();
			((FluidForce*)(particlesSystem->leadsForces[3]))->strength = fluidStrengthHandle.asFloat();


			MDataHandle noiseAmpHandle = data.inputValue (aNoiseAmp, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			//particlesSystem->noiseAmp =  cu::make_float3(noiseAmpHandle.asFloat(),noiseAmpHandle.asFloat(),noiseAmpHandle.asFloat());
			((TurbulenceForce*)(particlesSystem->leadsForces[2]))->noiseAmp = cu::make_float3(noiseAmpHandle.asFloat(),noiseAmpHandle.asFloat(),noiseAmpHandle.asFloat());


			MDataHandle noiseOffsetXHandle = data.inputValue (aNoiseOffsetX, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			float noiseOffsetX = noiseOffsetXHandle.asFloat();

			MDataHandle noiseOffsetYHandle = data.inputValue (aNoiseOffsetY, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			float noiseOffsetY = noiseOffsetYHandle.asFloat();

			MDataHandle noiseOffsetZHandle = data.inputValue (aNoiseOffsetZ, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			float noiseOffsetZ = noiseOffsetZHandle.asFloat();

			//particlesSystem->noiseOffset = cu::make_float3(noiseOffsetX,noiseOffsetY,noiseOffsetZ);
			((TurbulenceForce*)(particlesSystem->leadsForces[2]))->noiseOffset =cu::make_float3(noiseOffsetX,noiseOffsetY,noiseOffsetZ);

			MDataHandle noiseFreqHandle = data.inputValue (aNoiseFreq, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			//particlesSystem->noiseFreq = noiseFreqHandle.asFloat();
			((TurbulenceForce*)(particlesSystem->leadsForces[2]))->noiseFreq = noiseFreqHandle.asFloat();

			MDataHandle noiseOctHandle = data.inputValue (aNoiseOct, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			//particlesSystem->noiseOct = noiseOctHandle.asInt();
			((TurbulenceForce*)(particlesSystem->leadsForces[2]))->noiseOct = noiseOctHandle.asInt();

			MDataHandle noiseLacunHandle = data.inputValue (aNoiseLacun, &returnStatus);
			CHECK_MSTATUS( returnStatus );
			//particlesSystem->noiseLac = noiseLacunHandle.asFloat();
			((TurbulenceForce*)(particlesSystem->leadsForces[2]))->noiseLac = noiseLacunHandle.asFloat();
	
			MFnTransform fnTransform;
			MFnDagNode fnDag;
			MDagPath path;
			MPlugArray emittersArray;
			
			MPlug emittersPlug(this->thisMObject(),aEmitters);
			int nPlugs = emittersPlug.numElements();
			int conPlugs = emittersPlug.numConnectedElements();

			if (particlesSystem->nEmit != conPlugs){
				particlesSystem->nEmit = conPlugs;
				delete particlesSystem->emitters;
				particlesSystem->emitters = new ParticlesEmitter[conPlugs];
			}

			int k = 0;

			for ( unsigned int j=0; j<nPlugs; j++ ) {

					bool connected = emittersPlug[j].isConnected();

					if(connected) {
			
						emittersPlug[j].connectedTo(emittersArray, true, false);

						MObject emitter = emittersArray[0].node();

						fnDag.setObject(emitter);
						fnDag.getPath(path);

						fnTransform.setObject(path);

						MTransformationMatrix emitterMatrix = fnTransform.transformation();
						MVector pos = MTransformationMatrix(emitterMatrix).getTranslation(MSpace::kWorld);

						/*particlesSystem->emitters[k].posX = pos.x;
						particlesSystem->emitters[k].posY = pos.y;
						particlesSystem->emitters[k].posZ = pos.z;*/

						particlesSystem->emitters[k].pos = cu::make_float3(pos.x,pos.y,pos.z);

						MPlug amountPlug = fnDag.findPlug("amount",false);
						particlesSystem->emitters[k].amount = amountPlug.asDouble();

						MPlug radiusPlug = fnDag.findPlug("radius",false);
						particlesSystem->emitters[k].radius = radiusPlug.asDouble();

						/*particlesSystem->emitters[k].noiseVelAmpX = 0;
						particlesSystem->emitters[k].noiseVelAmpY = 0;
						particlesSystem->emitters[k].noiseVelAmpZ = 0;*/

						particlesSystem->emitters[k].noiseVelAmp = cu::make_float3(0,0,0);

						particlesSystem->emitters[k].noiseVelFreq = 0;
						particlesSystem->emitters[k].noiseVelLac = 0;
						particlesSystem->emitters[k].noiseVelOct = 0;
						/*particlesSystem->emitters[k].noiseVelOffsetX = 0;
						particlesSystem->emitters[k].noiseVelOffsetY = 0;
						particlesSystem->emitters[k].noiseVelOffsetZ = 0;*/
						particlesSystem->emitters[k].noiseVelOffset = cu::make_float3(0,0,0);

						particlesSystem->emitters[k].radVelAmp = 0;

						/*particlesSystem->emitters[k].velX = 0;
						particlesSystem->emitters[k].velY = 0;
						particlesSystem->emitters[k].velZ = 0;*/
						particlesSystem->emitters[k].vel = cu::make_float3(0,0,0);
			
						k++;
					}
			}

			MPlug fluidPlug(this->thisMObject(),aFluid);

			bool fluidConnected = fluidPlug.isConnected();

			if (fluidConnected) {
				MPlugArray fluidArray;
				fluidPlug.connectedTo( fluidArray, true, false );
				MObject fluidObject = fluidArray[0].node();

				fnDag.setObject(fluidObject);
				MPlug solverIdPlug = fnDag.findPlug("solverId",false);
				int sId = solverIdPlug.asInt();

				VHFluidSolver3D* curr3DSolver = VHFluidSolver3D::solverList[sId];
				//particlesSystem->fluidSolver = curr3DSolver;
				((FluidForce*)(particlesSystem->leadsForces[3]))->fluidSolver = curr3DSolver;


			}

			particlesSystem->emitParticles();
			particlesSystem->updateParticles();


			MDataHandle outTimeHandle = data.outputValue (aOutTime, &returnStatus);
			CHECK_MSTATUS(returnStatus);

			outTimeHandle.set(currentTime);

		}
		

	 } else {

		return MS::kUnknownParameter;
	}

	return MS::kSuccess;

}
