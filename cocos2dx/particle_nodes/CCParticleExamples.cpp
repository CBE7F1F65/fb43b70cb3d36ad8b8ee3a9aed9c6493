/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCParticleExamples.h"
#include "CCDirector.h"
#include "CCTextureCache.h"
#include "CCPointExtension.h"
namespace cocos2d {
//
// ParticleFire
//
bool CCParticleFire::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) )
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Gravity Mode
		this->m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		this->modeA.gravity = ccp(0,0);

		// Gravity Mode: radial acceleration
		this->modeA.radialAccel = 0;
		this->modeA.radialAccelVar = 0;

		// Gravity Mode: speed of particles
		this->modeA.speed = 60;
		this->modeA.speedVar = 20;		

		// starting angle
		m_fAngle = 90;
		m_fAngleVar = 10;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->m_tPosition = ccp(winSize.width/2, 60);
		this->m_tPosVar = ccp(40, 20);

		// life of particles
		m_fLife = 3;
		m_fLifeVar = 0.25f;


		// size, in pixels
		m_fStartSize = 54.0f;
		m_fStartSizeVar = 10.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per frame
		m_fEmissionRate = m_nTotalParticles/m_fLife;

		// color of particles
		m_tStartColor.r = 0.76f;
		m_tStartColor.g = 0.25f;
		m_tStartColor.b = 0.12f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 0.0f;
		m_tEndColor.g = 0.0f;
		m_tEndColor.b = 0.0f;
		m_tEndColor.a = 1.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(true);
		return true;
	}
	return false;
}
//
// ParticleFireworks
//
bool CCParticleFireworks::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) )
	{
		// duration
		m_fDuration= kCCParticleDurationInfinity;

		// Gravity Mode
		this->m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		this->modeA.gravity = ccp(0,-90);

		// Gravity Mode:  radial
		this->modeA.radialAccel = 0;
		this->modeA.radialAccelVar = 0;

		//  Gravity Mode: speed of particles
		this->modeA.speed = 180;
		this->modeA.speedVar = 50;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height/2);

		// angle
		this->m_fAngle= 90;
		this->m_fAngleVar = 20;

		// life of particles
		this->m_fLife = 3.5f;
		this->m_fLifeVar = 1;

		// emits per frame
		this->m_fEmissionRate = m_nTotalParticles/m_fLife;

		// color of particles
		m_tStartColor.r = 0.5f;
		m_tStartColor.g = 0.5f;
		m_tStartColor.b = 0.5f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.5f;
		m_tStartColorVar.g = 0.5f;
		m_tStartColorVar.b = 0.5f;
		m_tStartColorVar.a = 0.1f;
		m_tEndColor.r = 0.1f;
		m_tEndColor.g = 0.1f;
		m_tEndColor.b = 0.1f;
		m_tEndColor.a = 0.2f;
		m_tEndColorVar.r = 0.1f;
		m_tEndColorVar.g = 0.1f;
		m_tEndColorVar.b = 0.1f;
		m_tEndColorVar.a = 0.2f;

		// size, in pixels
		m_fStartSize = 8.0f;
		m_fStartSizeVar = 2.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// additive
		this->setIsBlendAdditive(false);
		return true;
	}
	return false;
}
//
// ParticleSun
//
bool CCParticleSun::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) )
	{
		// additive
		this->setIsBlendAdditive(true);

		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Gravity Mode
		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(0,0);

		// Gravity mode: radial acceleration
		modeA.radialAccel = 0;
		modeA.radialAccelVar = 0;

		// Gravity mode: speed of particles
		modeA.speed = 20;
		modeA.speedVar = 5;


		// angle
		m_fAngle = 90;
		m_fAngleVar = 360;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height/2);
		m_tPosVar = CCPointZero;

		// life of particles
		m_fLife = 1;
		m_fLifeVar = 0.5f;

		// size, in pixels
		m_fStartSize = 30.0f;
		m_fStartSizeVar = 10.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per seconds
		m_fEmissionRate = m_nTotalParticles/m_fLife;

		// color of particles
		m_tStartColor.r = 0.76f;
		m_tStartColor.g = 0.25f;
		m_tStartColor.b = 0.12f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 0.0f;
		m_tEndColor.g = 0.0f;
		m_tEndColor.b = 0.0f;
		m_tEndColor.a = 1.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		return true;
	}
	return false;
}

//
// ParticleGalaxy
//
bool CCParticleGalaxy::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) )
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Gravity Mode
		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(0,0);

		// Gravity Mode: speed of particles
		modeA.speed = 60;
		modeA.speedVar = 10;

		// Gravity Mode: radial
		modeA.radialAccel = -80;
		modeA.radialAccelVar = 0;

		// Gravity Mode: tagential
		modeA.tangentialAccel = 80;
		modeA.tangentialAccelVar = 0;

		// angle
		m_fAngle = 90;
		m_fAngleVar = 360;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height/2);
		m_tPosVar = CCPointZero;

		// life of particles
		m_fLife = 4;
		m_fLifeVar = 1;

		// size, in pixels
		m_fStartSize = 37.0f;
		m_fStartSizeVar = 10.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per second
		m_fEmissionRate = m_nTotalParticles/m_fLife;

		// color of particles
		m_tStartColor.r = 0.12f;
		m_tStartColor.g = 0.25f;
		m_tStartColor.b = 0.76f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 0.0f;
		m_tEndColor.g = 0.0f;
		m_tEndColor.b = 0.0f;
		m_tEndColor.a = 1.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(true);
		return true;
	}
	return false;
}

//
// ParticleFlower
//
bool CCParticleFlower::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) )
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Gravity Mode
		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(0,0);

		// Gravity Mode: speed of particles
		modeA.speed = 80;
		modeA.speedVar = 10;

		// Gravity Mode: radial
		modeA.radialAccel = -60;
		modeA.radialAccelVar = 0;

		// Gravity Mode: tagential
		modeA.tangentialAccel = 15;
		modeA.tangentialAccelVar = 0;

		// angle
		m_fAngle = 90;
		m_fAngleVar = 360;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height/2);
		m_tPosVar = CCPointZero;

		// life of particles
		m_fLife = 4;
		m_fLifeVar = 1;

		// size, in pixels
		m_fStartSize = 30.0f;
		m_fStartSizeVar = 10.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per second
		m_fEmissionRate = m_nTotalParticles/m_fLife;

		// color of particles
		m_tStartColor.r = 0.50f;
		m_tStartColor.g = 0.50f;
		m_tStartColor.b = 0.50f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.5f;
		m_tStartColorVar.g = 0.5f;
		m_tStartColorVar.b = 0.5f;
		m_tStartColorVar.a = 0.5f;
		m_tEndColor.r = 0.0f;
		m_tEndColor.g = 0.0f;
		m_tEndColor.b = 0.0f;
		m_tEndColor.a = 1.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(true);
		return true;
	}
	return false;
}
//
// ParticleMeteor
//
bool CCParticleMeteor::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) )
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Gravity Mode
		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(-200,200);

		// Gravity Mode: speed of particles
		modeA.speed = 15;
		modeA.speedVar = 5;

		// Gravity Mode: radial
		modeA.radialAccel = 0;
		modeA.radialAccelVar = 0;

		// Gravity Mode: tagential
		modeA.tangentialAccel = 0;
		modeA.tangentialAccelVar = 0;

		// angle
		m_fAngle = 90;
		m_fAngleVar = 360;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height/2);
		m_tPosVar = CCPointZero;

		// life of particles
		m_fLife = 2;
		m_fLifeVar = 1;

		// size, in pixels
		m_fStartSize = 60.0f;
		m_fStartSizeVar = 10.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per second
		m_fEmissionRate = m_nTotalParticles/m_fLife;

		// color of particles
		m_tStartColor.r = 0.2f;
		m_tStartColor.g = 0.4f;
		m_tStartColor.b = 0.7f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.2f;
		m_tStartColorVar.a = 0.1f;
		m_tEndColor.r = 0.0f;
		m_tEndColor.g = 0.0f;
		m_tEndColor.b = 0.0f;
		m_tEndColor.a = 1.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(true);
		return true;
	}
	return false;
}

//
// ParticleSpiral
//
bool CCParticleSpiral::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) ) 
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Gravity Mode
		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(0,0);

		// Gravity Mode: speed of particles
		modeA.speed = 150;
		modeA.speedVar = 0;

		// Gravity Mode: radial
		modeA.radialAccel = -380;
		modeA.radialAccelVar = 0;

		// Gravity Mode: tagential
		modeA.tangentialAccel = 45;
		modeA.tangentialAccelVar = 0;

		// angle
		m_fAngle = 90;
		m_fAngleVar = 0;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height/2);
		m_tPosVar = CCPointZero;

		// life of particles
		m_fLife = 12;
		m_fLifeVar = 0;

		// size, in pixels
		m_fStartSize = 20.0f;
		m_fStartSizeVar = 0.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per second
		m_fEmissionRate = m_nTotalParticles/m_fLife;

		// color of particles
		m_tStartColor.r = 0.5f;
		m_tStartColor.g = 0.5f;
		m_tStartColor.b = 0.5f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.5f;
		m_tStartColorVar.g = 0.5f;
		m_tStartColorVar.b = 0.5f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 0.5f;
		m_tEndColor.g = 0.5f;
		m_tEndColor.b = 0.5f;
		m_tEndColor.a = 1.0f;
		m_tEndColorVar.r = 0.5f;
		m_tEndColorVar.g = 0.5f;
		m_tEndColorVar.b = 0.5f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(false);
		return true;
	}
	return false;
}

//
// ParticleExplosion
//
bool CCParticleExplosion::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) ) 
	{
		// duration
		m_fDuration = 0.1f;

		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(0,0);

		// Gravity Mode: speed of particles
		modeA.speed = 70;
		modeA.speedVar = 40;

		// Gravity Mode: radial
		modeA.radialAccel = 0;
		modeA.radialAccelVar = 0;

		// Gravity Mode: tagential
		modeA.tangentialAccel = 0;
		modeA.tangentialAccelVar = 0;

		// angle
		m_fAngle = 90;
		m_fAngleVar = 360;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height/2);
		m_tPosVar = CCPointZero;

		// life of particles
		m_fLife = 5.0f;
		m_fLifeVar = 2;

		// size, in pixels
		m_fStartSize = 15.0f;
		m_fStartSizeVar = 10.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per second
		m_fEmissionRate = m_nTotalParticles/m_fDuration;

		// color of particles
		m_tStartColor.r = 0.7f;
		m_tStartColor.g = 0.1f;
		m_tStartColor.b = 0.2f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.5f;
		m_tStartColorVar.g = 0.5f;
		m_tStartColorVar.b = 0.5f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 0.5f;
		m_tEndColor.g = 0.5f;
		m_tEndColor.b = 0.5f;
		m_tEndColor.a = 0.0f;
		m_tEndColorVar.r = 0.5f;
		m_tEndColorVar.g = 0.5f;
		m_tEndColorVar.b = 0.5f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(false);
		return true;
	}
	return false;
}

//
// ParticleSmoke
//
bool CCParticleSmoke::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) )
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Emitter mode: Gravity Mode
		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(0,0);

		// Gravity Mode: radial acceleration
		modeA.radialAccel = 0;
		modeA.radialAccelVar = 0;

		// Gravity Mode: speed of particles
		modeA.speed = 25;
		modeA.speedVar = 10;

		// angle
		m_fAngle = 90;
		m_fAngleVar = 5;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, 0);
		m_tPosVar = ccp(20, 0);

		// life of particles
		m_fLife = 4;
		m_fLifeVar = 1;

		// size, in pixels
		m_fStartSize = 60.0f;
		m_fStartSizeVar = 10.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per frame
		m_fEmissionRate = m_nTotalParticles/m_fLife;

		// color of particles
		m_tStartColor.r = 0.8f;
		m_tStartColor.g = 0.8f;
		m_tStartColor.b = 0.8f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.02f;
		m_tStartColorVar.g = 0.02f;
		m_tStartColorVar.b = 0.02f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 0.0f;
		m_tEndColor.g = 0.0f;
		m_tEndColor.b = 0.0f;
		m_tEndColor.a = 1.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(false);
		return true;
	}
	return false;
}
//
// CCParticleSnow
//
bool CCParticleSnow::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) ) 
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// set gravity mode.
		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(0,-1);

		// Gravity Mode: speed of particles
		modeA.speed = 5;
		modeA.speedVar = 1;

		// Gravity Mode: radial
		modeA.radialAccel = 0;
		modeA.radialAccelVar = 1;

		// Gravity mode: tagential
		modeA.tangentialAccel = 0;
		modeA.tangentialAccelVar = 1;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height + 10);
		m_tPosVar = ccp( winSize.width/2, 0 );

		// angle
		m_fAngle = -90;
		m_fAngleVar = 5;

		// life of particles
		m_fLife = 45;
		m_fLifeVar = 15;

		// size, in pixels
		m_fStartSize = 10.0f;
		m_fStartSizeVar = 5.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per second
		m_fEmissionRate = 10;

		// color of particles
		m_tStartColor.r = 1.0f;
		m_tStartColor.g = 1.0f;
		m_tStartColor.b = 1.0f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 1.0f;
		m_tEndColor.g = 1.0f;
		m_tEndColor.b = 1.0f;
		m_tEndColor.a = 0.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(false);
		return true;
	}
	return false;
}
//
// CCParticleRain
//
bool CCParticleRain::initWithTotalParticles(int numberOfParticles)
{
	if( ARCH_OPTIMAL_PARTICLE_SYSTEM::initWithTotalParticles(numberOfParticles) )
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		m_nEmitterMode = kCCParticleModeGravity;

		// Gravity Mode: gravity
		modeA.gravity = ccp(10,-10);

		// Gravity Mode: radial
		modeA.radialAccel = 0;
		modeA.radialAccelVar = 1;

		// Gravity Mode: tagential
		modeA.tangentialAccel = 0;
		modeA.tangentialAccelVar = 1;

		// Gravity Mode: speed of particles
		modeA.speed = 130;
		modeA.speedVar = 30;

		// angle
		m_fAngle = -90;
		m_fAngleVar = 5;


		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		m_tPosition = ccp(winSize.width/2, winSize.height);
		m_tPosVar = ccp( winSize.width/2, 0 );

		// life of particles
		m_fLife = 4.5f;
		m_fLifeVar = 0;

		// size, in pixels
		m_fStartSize = 4.0f;
		m_fStartSizeVar = 2.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per second
		m_fEmissionRate = 20;

		// color of particles
		m_tStartColor.r = 0.7f;
		m_tStartColor.g = 0.8f;
		m_tStartColor.b = 1.0f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 0.7f;
		m_tEndColor.g = 0.8f;
		m_tEndColor.b = 1.0f;
		m_tEndColor.a = 0.5f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		// additive
		this->setIsBlendAdditive(false);
		return true;
	}
	return false;
}

}//namespace cocos2d
