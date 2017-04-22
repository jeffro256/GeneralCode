//
//  GameScene.swift
//  Zombie Conga
//
//  Created by Jeffrey Ryan on 2/21/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    var zombie = SKSpriteNode(imageNamed: "zombie1")
    let zombieSpeed: CGFloat = 400
    let zombieRotateSpeed = π * 2
    var lastUpdateTime: NSTimeInterval = 0
    var lastTapLocation = CGPointZero
    var hasTapped = false
    
    let playableRect: CGRect
    
    override init(size: CGSize) {
        let maxAspectRatio: CGFloat = 16 / 9
        let playableHeight = size.width / maxAspectRatio
        let margin = (size.height - playableHeight) / 2
        playableRect = CGRect(x: 0, y: margin, width: size.width, height: playableHeight)
        super.init(size: size)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func didMoveToView(view: SKView) {
        self.backgroundColor = .whiteColor()
        
        var background = SKSpriteNode(imageNamed: "Images/background1.png")
        background.position = CGPoint(x: CGRectGetMidX(frame), y: CGRectGetMidY(frame))
        background.zPosition = -1
        addChild(background)
        
        zombie.position = CGPoint(x: 400, y: 400)
        addChild(zombie)
        
        lastTapLocation = zombie.position + CGPoint(x: 1, y: 0)
    }
    
    func getVelocityTowardsPoint(target: CGPoint, position: CGPoint, vel: CGFloat) -> CGVector {
        let dx = target.x - position.x
        let dy = target.y - position.y
        let dist = (target - position).length()
        let offset = CGVector(dx: vel / dist * dx, dy: vel / dist * dy)
        return offset
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        let location = touches.anyObject()!.locationInNode(self)
        
        if (playableRect.contains(location)) {
            lastTapLocation = location
        }
        hasTapped = true
    }
    
    override func touchesMoved(touches: NSSet, withEvent event: UIEvent) {
        let location = touches.anyObject()!.locationInNode(self)
        
        if (playableRect.contains(location)) {
            lastTapLocation = location
        }
        hasTapped = true
    }
    
    override func update(currentTime: NSTimeInterval) {
        var elapsed: NSTimeInterval
        
        if lastUpdateTime == 0 {
            elapsed = 0
        }
        else {
            elapsed = currentTime - lastUpdateTime
        }
        
        let zombieVelocity = getVelocityTowardsPoint(lastTapLocation, position: zombie.position, vel: zombieSpeed)
        let zombieOffset = CGVectorMake(zombieVelocity.dx * CGFloat(elapsed), zombieVelocity.dy * CGFloat(elapsed))
        if (lastTapLocation - zombie.position).length() > zombieOffset.length() && hasTapped {
            zombie.position += zombieOffset
        }
        
        let preferredRotation = shortestAngleBetweenAngles(zombie.zRotation, atan2(zombieVelocity.dy, zombieVelocity.dx))
        let rotationOffset = preferredRotation * zombieRotateSpeed * CGFloat(elapsed)
        
        if abs(preferredRotation - zombie.zRotation) > abs(rotationOffset) && hasTapped {
            zombie.zRotation += rotationOffset
        }
        
        lastUpdateTime = currentTime
    }
}
