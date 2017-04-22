//
//  GameScene.swift
//  Wall Jam
//
//  Created by Jeffrey Ryan on 2/26/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    var worldNode: SKNode!
    var map: JSTileMap!
    var player: Player!
    var mapSize: CGSize!
    
    func buildCharacters() {
        player = Player()
        player.zPosition = 50
        player.position = CGPoint(x: 300, y: 300)
        worldNode.addChild(player)
    }
    
    func buildWorld() {
        self.anchorPoint = CGPointZero
        self.physicsWorld.gravity = CGVectorZero
        self.position = CGPointZero
        
        worldNode = SKNode()
        worldNode.position = CGPointZero
        
        map = JSTileMap(named: "level-3-sample.tmx")!
        map.position = CGPointZero
        
        mapSize = CGSizeMake(map.mapSize.width * map.tileSize.width, map.mapSize.height * map.tileSize.height)

        worldNode.physicsBody = SKPhysicsBody(edgeLoopFromRect: CGRect(origin: CGPointZero, size: mapSize))
        worldNode.physicsBody!.friction = 0
        
        //worldNode.addChild(map)
        
        addChild(map)
    }
    
    func getCenterViewOn(target: CGPoint) -> CGPoint {
        let x = target.x.clamped(size.width / 2, mapSize.width - size.width / 2)
        let y = target.y.clamped(size.height / 2, mapSize.height - size.height / 2)
        
        return CGPointMake(-x, -y)
    }
    
    override func didMoveToView(view: SKView) {
        /* Setup your scene here */
        buildWorld()
        buildCharacters()
        worldNode.position = getCenterViewOn(player.position)
    }
    
    override func didSimulatePhysics() {
        //let target = getCenterViewOn(player.position)
        
        //worldNode.position += (target - worldNode.position) * 0.1
    }
    
    /*
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        //let touchLocation = touches.anyObject()!.locationInNode(worldNode)
        
        //player.moveToward(touchLocation)
    }
    */

    override func update(currentTime: CFTimeInterval) {
        /* Called before each frame is rendered */
    }
}
