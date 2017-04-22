//
//  GameViewController.swift
//  Zombie Conga
//
//  Created by Jeffrey Ryan on 2/21/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import UIKit
import SpriteKit

class GameViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()

        let sceneSize = CGSize(width: 2048, height: 1536)
        let sceneView = self.view as SKView
        let scene = GameScene(size: sceneSize)
        
        sceneView.showsFPS = true
        sceneView.showsNodeCount = true
        sceneView.ignoresSiblingOrder = true
        
        scene.scaleMode = .AspectFill
        sceneView.presentScene(scene)
    }

    override func prefersStatusBarHidden() -> Bool {
        return true
    }
}
