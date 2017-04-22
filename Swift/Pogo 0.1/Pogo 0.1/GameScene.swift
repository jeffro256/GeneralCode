//
//  GameScene.swift
//  Pogo 0.1
//
//  Created by Jeffrey Ryan on 5/18/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    var worldNode: SKNode = SKNode()
    var lastTime: NSTimeInterval = 0
    
    override init(size: CGSize) {
        super.init(size: size)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func didMoveToView(view: SKView) {
        super.didMoveToView(view)
        setupSceneAndWorld()
        createCharacters()
    }
    
    override func touchesBegan(touches: Set<NSObject>, withEvent event: UIEvent) {
        let head = worldNode.childNodeWithName("head")!
        
        for touch in (touches as! Set<UITouch>) {
            let touchLocation = touch.locationInNode(worldNode)
            let forceAngle = (touchLocation - head.position).angle
            let forceMagnitude: CGFloat = (touchLocation - head.position).length() * 100
            
            head.physicsBody?.applyImpulse(CGVector(angle: forceAngle) * forceMagnitude)
        }
    }
    
    override func update(currentTime: NSTimeInterval) {
        if lastTime == 0 {
            lastTime = currentTime
            return
        }
        
        let elapsedTime = currentTime - lastTime
        
        let head = worldNode.childNodeWithName("head")!
        let pogo = worldNode.childNodeWithName("pogo")!
        let angleFromPogo = (head.position - pogo.position).angle
        var forceAngle = angleFromPogo + (angleFromPogo >= π / 2 ? -π / 2 : π / 2)
        let forceMagnitude = abs(angleFromPogo - π / 2) * 100
        let forceVector = CGVector(angle: forceAngle) * forceMagnitude
        
        if angleFromPogo - π / 2 > 0.15 {
            head.physicsBody?.applyImpulse(forceVector)
        }
        
        println(forceAngle)
        
        lastTime = currentTime
    }
    
    func setupSceneAndWorld() {
        self.backgroundColor = .blueColor()
        self.anchorPoint = CGPoint(x: 0.5, y: 0.5)
        self.physicsWorld.speed = 1.0 / 4.0
        
        worldNode = SKNode()
        
        var worldBody = SKPhysicsBody(edgeLoopFromRect: self.frame)
        worldBody.categoryBitMask = CollisionTypes.World
        worldBody.friction = 0
        
        worldNode.physicsBody = worldBody
        
        self.addChild(worldNode)
    }
    
    func createCharacters() {
        let head = SKSpriteNode(imageNamed: "head")
        let pogo = SKSpriteNode(color: UIColor.greenColor(), size: CGSize(width: 15, height: 75))
        
        head.name = "head"
        pogo.name = "pogo"
        
        head.size = CGSize(width: 35, height: 35)
        
        head.position = CGPointZero
        pogo.position = CGPoint(x: head.position.x, y: head.position.y - pogo.size.height / 2 - head.size.height / 2)
        
        let headBody = SKPhysicsBody(circleOfRadius: head.size.width / 2)
        let pogoBodyBottom = SKPhysicsBody(circleOfRadius: pogo.size.width / 2, center: CGPoint(x: 0, y: -pogo.size.height / 2 + pogo.size.width / 2))
        
        headBody.categoryBitMask = CollisionTypes.Head
        pogoBodyBottom.categoryBitMask = CollisionTypes.Pogo
        
        headBody.collisionBitMask = CollisionTypes.All ^ CollisionTypes.Pogo
        pogoBodyBottom.collisionBitMask = CollisionTypes.All ^ CollisionTypes.Head
        
        headBody.mass = 10
        pogoBodyBottom.mass = 30
        
        head.physicsBody = headBody
        pogo.physicsBody = pogoBodyBottom
        
        worldNode.addChild(head)
        worldNode.addChild(pogo)
        
        let joint = SKPhysicsJointFixed.jointWithBodyA(headBody, bodyB: pogoBodyBottom, anchor: head.position)
        self.physicsWorld.addJoint(joint)
    }
}
