//
//  GameScene.swift
//  JSTileMapTest2
//
//  Created by Jeffrey Ryan on 3/25/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    var map: JSTileMap!
    var mapSize: CGSize!
    
    override func didMoveToView(view: SKView) {
        self.anchorPoint = CGPoint(x: 0.5, y: 0.5)
        
        map = JSTileMap(named: "maps/alpha1_1.tmx")
        
        //var path = NSBundle.mainBundle().pathForResource("alpha1_1", ofType: "tmx")
        //var str = String(contentsOfFile: path!, encoding: NSUTF8StringEncoding, error: nil)
        //println(str)
        //println(map)
        mapSize = CGSize(width: map.mapSize.width * map.tileSize.width, height: map.mapSize.height * map.tileSize.height)
        
        map.position = CGPoint(x: -mapSize.width / 2, y: -mapSize.height / 2)
        
        if map != nil {
            addChild(map!)
        }
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        let location = touches.anyObject()?.locationInNode(self)
        
        map.runAction(SKAction.moveByX(-location!.x, y: -location!.y, duration: 0.0))
        //joffrey and vishar and hin young kim and heven
    }
}
