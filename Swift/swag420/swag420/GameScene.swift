//
//  GameScene.swift
//  swag420
//
//  Created by Jeffrey Ryan on 4/7/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    override func didMoveToView(view: SKView) {
        var coolNode = SKSpriteNode(color: UIColor.whiteColor(), size: CGSize(width: 20, height: 100))
        coolNode.position = CGPoint(x: 20, y: 100);
        
        addChild(coolNode)
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        
    }
   
    override func update(currentTime: CFTimeInterval) {
        /* Called before each frame is rendered */
    }
}
