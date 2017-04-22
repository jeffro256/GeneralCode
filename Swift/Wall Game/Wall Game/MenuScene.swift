//
//  MenuScene.swift
//  Wall Game
//
//  Created by Jeffrey Ryan on 2/15/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class MenuScene: SKScene {
    var ball = SKSpriteNode()
    var testSquare = SKSpriteNode()
    
    var lastShootTime = NSTimeInterval(0)
    
    override func didMoveToView(view: SKView) {
        super.didMoveToView(view)
        
        println(self.view!.frame)
        
        physicsWorld.gravity = CGVector(dx: 0, dy: 0)
        
        var ballTexture = SKTexture(imageNamed: "ball.png")
        ball = SKSpriteNode(texture: ballTexture)
        ball.name = "Ball"
        ball.position = CGPoint(x: CGRectGetMidX(frame), y: CGRectGetMidY(frame))
        ball.size = CGSize(width: 75, height: 75)
        
        ball.physicsBody = SKPhysicsBody(circleOfRadius: ball.size.width / 2)
        ball.physicsBody?.allowsRotation = false
        ball.physicsBody?.angularDamping = 0
        ball.physicsBody?.dynamic = true
        ball.physicsBody?.friction = 0
        ball.physicsBody?.linearDamping = 0
        ball.physicsBody?.restitution = 1
        
        addChild(ball)
        // now scene frame
        var borderBody = SKPhysicsBody(edgeLoopFromRect: self.frame)
        borderBody.friction = 0
        physicsBody = borderBody
        
        // do stuff 4 square
        testSquare = SKSpriteNode(color: UIColor.redColor(), size: CGSize(width: 50, height: 50))
        testSquare.name = "Test Square"
        testSquare.position = CGPoint(x: CGRectGetMidX(frame) + 100, y: CGRectGetMidY(frame))
        
        addChild(testSquare)
    }
    
    override func touchesBegan(touches: Set<NSObject>, withEvent event: UIEvent) {
        super.touchesBegan(touches, withEvent: event)
        
        let location = (touches.first as! UITouch).locationInNode(self)
        
        let Fx = Int(arc4random_uniform(200)), Fy = Int(arc4random_uniform(200))
        ball.physicsBody?.applyImpulse(CGVector(dx: Fx, dy: Fy))
        
        var crackTexture = SKTexture(imageNamed: "cracked.png")
        var crack = SKSpriteNode(texture: crackTexture)
        crack.position = location
        crack.size = CGSize(width: 60, height: 60)
        
        addChild(crack)
    }
    
    override func update(currentTime: NSTimeInterval) {
        super.update(currentTime)
        
        testSquare.zRotation += 0.01
        
        if (currentTime - lastShootTime >= 0.5) {
            let dist = 800
            var dx: CGFloat = cos(testSquare.zRotation) * CGFloat(dist)
            var dy: CGFloat = sin(testSquare.zRotation) * CGFloat(dist)
            var targetPoint = CGPoint(x: testSquare.position.x + dx, y: testSquare.position.y + dy)
            var moveProjectile = SKAction.moveTo(targetPoint, duration: NSTimeInterval(dist / 300))
            var moveAndRemove = SKAction.sequence([moveProjectile, SKAction.removeFromParent()])
            
            let projectileTexture = SKTexture(imageNamed: "bullet.png")
            var projectile = SKSpriteNode(texture: projectileTexture)
            projectile.position = testSquare.position
            projectile.zRotation = testSquare.zRotation
            projectile.size = CGSize(width: 35, height: 35)
            projectile.runAction(moveAndRemove)
            
            addChild(projectile)
            
            lastShootTime = currentTime
        }
    }
}