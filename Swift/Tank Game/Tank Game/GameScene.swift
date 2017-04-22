//
//  GameScene.swift
//  Tank Game
//
//  Created by Jeffrey Ryan on 2/18/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    override func didMoveToView(view: SKView) {
        super.didMoveToView(view)
        
        let wallTexture = SKTexture(imageNamed: "dirt.png")!
        let wallWidth = 128
        let wallHeight = 128
        let frameWidth = Int(ceil(self.frame.width / CGFloat(wallWidth))) + 1
        let frameHeight = Int(ceil(self.frame.width / CGFloat(wallWidth))) + 1
        
        let moveWall = SKAction.moveBy(CGVector(dx: 0, dy: -wallHeight), duration: NSTimeInterval(1))
        let resetWall = SKAction.moveBy(CGVector(dx: 0, dy: wallHeight), duration: 0)
        let wallAction = SKAction.repeatActionForever(SKAction.sequence([moveWall, resetWall]))
        
        for var i = 0; i < frameWidth; i++ {
            for var j = 0; j < frameHeight; j++ {
                var wallNode = SKSpriteNode(texture: wallTexture)
                wallNode.position = CGPoint(x: wallWidth / 2 + wallWidth * i, y: wallHeight / 2 + wallHeight * j)
                wallNode.size = CGSize(width: wallWidth, height: wallHeight)
                wallNode.runAction(wallAction)
                
                self.addChild(wallNode)
            }
        }
    }
    
    /*
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
    }*/
   
    override func update(currentTime: CFTimeInterval) {
        /* Called before each frame is rendered */
    }
}
