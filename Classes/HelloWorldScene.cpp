#include "HelloWorldScene.h"
#include "PhysicsShapeCache.h"
#include "MyBodyParser.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,-9.8));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
   
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    PhysicsBody * egdnode = PhysicsBody::createEdgeBox(visibleSize,PhysicsMaterial(0,1,0),3);
    Node * node = Node::create();
    egdnode->setCategoryBitmask(0x001);
    egdnode->setCollisionBitmask(0x001);
    egdnode->setContactTestBitmask(true);
    //node->setAnchorPoint(Point(0,0));
    //CCLOG("origin la: %f",origin.y);
    node->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    node->setPhysicsBody(egdnode);
    this->addChild(node);
   
    
        Sprite *ball = Sprite::create("32.png");
        ball->setScale(0.5, 0.5);
        ball->setAnchorPoint(Point(0.5,0.5));
        ball->setPosition(Point(visibleSize.width/2,visibleSize.height + random(2, 4)));
        auto * physBall= PhysicsBody::createBox(ball->getContentSize(),PhysicsMaterial(0,1,0));
        physBall->setContactTestBitmask(true);
        physBall->setCategoryBitmask(0x001);
        //physBall->setVelocity(Vect(100,0));
        //physBall->setLinearDamping(1);
        //physBall->applyForce(Vect(55,35));
        physBall->applyImpulse(Vect(0,70));
        physBall->setCollisionBitmask(0x003);
        ball->setPhysicsBody(physBall);
    
    
    
       Sprite *ball2 = Sprite::create("bottle.png");
//        //ball->setScale(0.5, 0.5);
//        ball->setAnchorPoint(Point(0.5,0.5));
        ball2->setPosition(Point(visibleSize.width/2,visibleSize.height/2 + random(2, 4)));
//        auto * physBall= PhysicsBody::createBox(ball->getContentSize(),PhysicsMaterial(0,1,0));
//        physBall->setContactTestBitmask(true);
//        physBall->setCollisionBitmask(1);
        //MyBodyParser::getInstance()->parseJsonFile("download.json");
       // auto *phys= MyBodyParser::getInstance()->bodyFormJson(ball, "download");
        //ball->setPhysicsBody(phys);
        PhysicsShapeCache::getInstance()->addShapesWithFile("bottle.plist");
        PhysicsShapeCache::getInstance()->setBodyOnSprite("bottle", ball2);
        ball2->getPhysicsBody()->setCategoryBitmask(0x001);
        ball2->getPhysicsBody()->setCollisionBitmask(0x003);
        ball2->setPosition(Vect(ball2->getPhysicsBody()->getPosition()));
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin  = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    auto *joint =PhysicsJointDistance::construct(ball->getPhysicsBody(),ball2->getPhysicsBody(), Vect(60,20), Vect(50,50));
//    PhysicsWorld * w= this->getPhysicsWorld();
//    w->addJoint(joint);
    this->addChild(ball2);
    this->addChild(ball);
    Vec2 points[5];
    int num = 0;
    // raycastcallbackfunc
    auto func = [&points, &num](PhysicsWorld& world,
                                const PhysicsRayCastInfo& info, void* data)->bool
    {
        if (num < 5)
        {
            points[num++] = info.contact;
        }
        return true;
    };
    
    // set up camera
    auto *cameraLayer = Layer::create();
    cameraLayer->setTag(5);
    cameraLayer->setRotation3D(Vec3(50, 100, 20));
    addChild(cameraLayer);
    auto *camera = new ActionCamera();
    camera->autorelease();
    camera->setTarget(cameraLayer);
    auto eye = camera->getEye();
    eye . y =  - 20 ;
    camera->setEye(eye);
    this->runAction(camera);
    //camera->setCenter(eye);
    return true;
}

bool HelloWorld::onContactBegin(PhysicsContact & contact){
    PhysicsBody * A = contact.getShapeA()->getBody();
    PhysicsBody * B = contact.getShapeB()->getBody();
    CCLOG("fsdfs");
    return true;
}

PhysicsWorld* HelloWorld::getPhysicsWorld(){
    return sceneWorld;
}