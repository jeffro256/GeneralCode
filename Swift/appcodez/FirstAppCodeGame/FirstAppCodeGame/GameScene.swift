//
//  GameScene.swift
//  FirstAppCodeGame
//
//  Created by Jeffrey Ryan on 4/17/15.
//  Copyright (c) 2015 Fish In Space. All rights reserved.
//

import SpriteKit

enum CollideTypes {
    static let None:     UInt32 = 0
    static let All:      UInt32 = UInt32.max
    static let Boundary: UInt32 = 1 << 0
    static let Paddle:   UInt32 = 1 << 1
    static let Ball:     UInt32 = 1 << 2
}

class GameScene: SKScene {
    var paddleSize: CGSize
    var leftPaddle, rightPaddle: SKSpriteNode

    override init(size: CGSize) {
        self.paddleSize = CGSize()
        self.leftPaddle = SKSpriteNode()
        self.rightPaddle = SKSpriteNode()

        super.init(size: size)
    }

    required init?(coder: NSCoder) {
        fatalError("coder is not set up in GameScene")
    }

    override func didMoveToView(view: SKView) {
        self.backgroundColor = .blackColor()
        self.physicsWorld.gravity = CGVector(dx: 0, dy: 0)

        self.paddleSize = CGSize(width: self.frame.width / 15, height: self.frame.height / 4)
        self.leftPaddle = SKSpriteNode(color: .whiteColor(), size: paddleSize)
        self.rightPaddle = SKSpriteNode(color: .whiteColor(), size: paddleSize)

        self.leftPaddle.position = CGPoint(x: CGRectGetMidX(self.frame), y: CGRectGetMidY(self.frame))

        self.addChild(leftPaddle)
        self.addChild(rightPaddle)

        self.rightPaddle.runAction(SKAction.moveByX(1000, y: 1000, duration: 5))

        println(self.frame.size)
    }
    
    override func touchesBegan(touches: Set<NSObject>, withEvent event: UIEvent) {
        for touch in (touches as! Set<UITouch>) {

        }
    }
   
    override func update(currentTime: CFTimeInterval) {
        /* Called before each frame is rendered */
    }
}
