//
//  TileMapHelpers.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 3/28/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

func createPhysicsBodiesForMap(_ map: JSTileMap) {
    let baseLayer = map.layerNamed("Background")
    
    for col in 0..<Int(map.mapSize.width) {
        for row in 0..<Int(map.mapSize.height) {
            let coord = CGPoint(x: col, y: row)
            let gid = baseLayer?.layerInfo.tileGid(atCoord: coord)
            
            if gid == 0 {
                continue
            }
            
            if let properties = map.properties(forGid: gid!) {
                if let hitbox = properties["hitbox"] as? String {
                    switch (hitbox) {
                    case "full":
                        let tile = baseLayer?.tile(atCoord: coord)
                        
                        tile?.physicsBody = SKPhysicsBody(rectangleOf: (tile?.size)!)
                        tile?.physicsBody?.categoryBitMask = CollisionTypes.Block
                        tile?.physicsBody?.collisionBitMask = CollisionTypes.None
                        tile?.physicsBody?.isDynamic = false
                        tile?.physicsBody?.friction = 0
                    default:
                        print("Hitbox literal '\(hitbox)' is not understood.")
                    }
                }
            }
        }
    }
}

func createObjectsForMap(_ map: JSTileMap) {
    if let playerObj = map.groupNamed("Players").objectNamed("Player") {
        let player = Player(spriteName: "matthew")
        
        let x = playerObj["x"] as? NSNumber
        let y = playerObj["y"] as? NSNumber
        
        player.position = CGPoint(x: CGFloat(x!), y: CGFloat(y!))
        
        map.addChild(player)
    }
    
    if let enemyObjects = map.groupNamed("Enemies").objectsNamed("Enemy") as? [[String: AnyObject]] {
        for enemyObj in enemyObjects {
            let enemy = Enemy(spriteName: "ghost")
            
            let x = enemyObj["x"] as? NSNumber
            let y = enemyObj["y"] as? NSNumber
            
            enemy.position = CGPoint(x: CGFloat(x!), y: CGFloat(y!))
            
            map.addChild(enemy)
        }
    }
}
