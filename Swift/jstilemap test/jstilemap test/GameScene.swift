//
//  GameScene.swift
//  jstilemap test
//
//  Created by Jeffrey Ryan on 3/24/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    override func didMoveToView(view: SKView) {
        var map = JSTileMap(named: "alpha.tmx")
        
        addChild(map)
    }
}
