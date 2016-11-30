#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/CollisionBox2D.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>

#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>

#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>

#include "Toolkit.h"

#include "Fighter.h"
#include "Missile.h"
#include "ControlsList.h"
#include "Bullet.h"
#include "AP.h"
#include "BUFF.h"
#include "HeatSource.h"
#include "Skill.h"
#include "Skill_Missile.h"
#include "Skill_Flare.h"
#include "Skill_Blink.h"

#define PI 3.1415926

Fighter::Fighter(Context* context) : GameObject(context)
{
	///Set original staus
	SetMaxHp(100.0f);
	SetHp(GetMaxHp());
	SetMass(10.0f);
	SetCollisionSize(Vector2(0.32f, 0.32f));
	SetInvincible(false);
	SetSpeed(0.0f);
	SetMaxSpeed(5.0f);
	SetDamping(0.015f);
	SetAcceleration(0.03f);
	SetBrake(0.05f);
	SetTowards(Vector3(0.0f, 1.0f, 0.0f));
	SetTurningVelocity(100.0f);
	SetBulletType("AP");
	///Set bullets type
	///Test bullets
	testcnt_ = 0;
}

void Fighter::RegisterObject(Context* context)
{
	context->RegisterFactory<Fighter>();
}

void Fighter::InitiateWeapons()
{
	///Initiate bullets

}

void Fighter::Start()
{
	Node* node = GetNode();

	/// sprite
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Sprite2D* sprite2d = cache->GetResource<Sprite2D>("Urho2D/fighter.png");
	StaticSprite2D* staticsprite = node->CreateComponent<StaticSprite2D>();
	staticsprite->SetColor(Color(Random(1.0f), Random(1.0f), Random(1.0f)));
	staticsprite->SetSprite(sprite2d);

	/// Add rigidbody
	rigibody2d_ = node->CreateComponent<RigidBody2D>();
	rigibody2d_->SetBodyType(BT_DYNAMIC);
	rigibody2d_->SetMass(GetMass());

	/// Add collisionbox
	collisionbox2d_ = node->CreateComponent<CollisionBox2D>();
	collisionbox2d_->SetSize(GetCollisionSize());

	/// BUFF
	// HeatSource
	HeatSource* heatsource_ = node->CreateComponent<HeatSource>();
	heatsource_->SetOwner(SharedPtr<Node>(node));
	heatsource_->SetAttraction(3.0f);

	/// Skills
	// Missile
	Skill_Missile* skillMissile = node->CreateComponent<Skill_Missile>();
	skillMissile->SetTriggerKey(CTRL_Q);
	// Flare
	Skill_Flare* skillFlare = node->CreateComponent<Skill_Flare>();
	skillFlare->SetTriggerKey(CTRL_W);
	// Blink
	Skill_Blink* skillBlink = node->CreateComponent<Skill_Blink>();
	skillBlink->SetTriggerKey(CTRL_E);
	/// Add some static buff to the fighter
	//node->CreateComponent<HeatSource>();
}

void Fighter::FixedUpdate(float timeStep)
{
	Node* node = GetNode();
	///Acceleration
	if (controls_.IsDown(CTRL_UP)) {
		Accelerate();
	}
	///Damping
	else {
		Damping();
	}
	///Braking
	if (controls_.IsDown(CTRL_DOWN)) {
		Brake();
	}
	///Turn left
	if (controls_.IsDown(CTRL_LEFT)) {
		//Turn left
		//towards_ = Vector3(towards_.x_*cos(turningVelocity_*timeStep) - towards_.y_*sin(turningVelocity_*timeStep), towards_.x_*sin(turningVelocity_*timeStep) + towards_.y_*cos(turningVelocity_*timeStep), 0.0f);		
		node->Rotate2D(turningVelocity_*timeStep);
		// The angle between rotation2d and x-axis
		float angle = 90.0f + node->GetRotation2D();
		// The towards vector according to the angle
		towards_ = Vector3(cos(angle * PI / 180.0f), sin(angle * PI / 180.0f), 0.0f);
	}
	///Turn right
	if (controls_.IsDown(CTRL_RIGHT)) {
		//Turn right
		//towards_ = Vector3(towards_.x_*cos(turningVelocity_*timeStep) + towards_.y_*sin(turningVelocity_*timeStep), -towards_.x_*sin(turningVelocity_*timeStep) + towards_.y_*cos(turningVelocity_*timeStep), 0.0f);	
		node->Rotate2D(-turningVelocity_*timeStep);
		// The angle between rotation2d and x-axis
		float angle = 90.0f + node->GetRotation2D();
		// The towards vector according to the angle
		towards_ = Vector3(cos(angle * PI / 180.0f), sin(angle * PI / 180.0f), 0.0f);
	}
	/// 4Test
	if (controls_.IsDown(CTRL_SPACE)) {
		Fire();
	}

	///Rotate the fighter
	//node->SetRotation(Quaternion(Vector3(0.0f, 1.0f, 0.0f), towards_));

	///Impulse the fighter(may be not true)
	rigibody2d_->SetLinearVelocity(Vector2(towards_.x_, towards_.y_).Normalized() * speed_);

	/// If the fighter'hp <=0 ,then desory it.
	if (GetHp() <= 0.0f) this->Destoryed();

}

void Fighter::Fire()
{
	Node* node = GetNode();
	Scene* scene = GetScene();

	// 4test
	// Only for test
	if (bulletType_ == "AP") {
		testcnt_++;
		if (testcnt_ < 15)  return;
		Node* bullet0 = scene->CreateChild("bullet", REPLICATED);
		bullet0->CreateComponent<AP>();
		// Set the ownership of the bullet to the fighter
		bullet0->GetComponent<AP>()->SetProducer(node);
		// Set the position and rotation of the bullet
		bullet0->SetWorldPosition(node->GetPosition() + towards_.Normalized()*0.2f);
		bullet0->SetWorldRotation(Quaternion(Vector3::UP, towards_));
		bullet0->GetComponent<RigidBody2D>()->SetLinearVelocity(Vector2(towards_.x_, towards_.y_).Normalized() * 10.0f);
		testcnt_ = 0;
	}
}

void Fighter::Destoryed()
{
	Node* node = GetNode();
	node->Remove();
}