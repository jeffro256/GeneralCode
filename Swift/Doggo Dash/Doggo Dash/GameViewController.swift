//
//  GameViewController.swift
//  Doggo Dash
//
//  Created by Jeffrey Ryan on 1/8/16.
//  Copyright (c) 2016 Jeffrey Ryan. All rights reserved.
//

import UIKit
import SpriteKit

var mainGameScene: GameScene?

class GameViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()

        let skView = self.view as! SKView
        //skView.showsFPS = true
        //skView.showsNodeCount = true
        //skView.showsPhysics = true
        skView.ignoresSiblingOrder = true

        mainGameScene = GameScene(size: skView.bounds.size)
        mainGameScene?.scaleMode = .AspectFill

        skView.presentScene(mainGameScene)
    }

    override func shouldAutorotate() -> Bool {
        return true
    }

    override func supportedInterfaceOrientations() -> UIInterfaceOrientationMask {
        return .Landscape
    }

    override func prefersStatusBarHidden() -> Bool {
        return true
    }
}
