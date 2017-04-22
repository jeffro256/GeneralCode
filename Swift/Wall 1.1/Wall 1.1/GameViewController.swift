//
//  GameViewController.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 3/25/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import UIKit
import SpriteKit

class GameViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()

        let skView = self.view as! SKView
        skView.showsFPS = false
        skView.showsNodeCount = false
        skView.ignoresSiblingOrder = false
        
        let scene = MenuScene(size: self.view.bounds.size)
        scene.scaleMode = .aspectFill

        skView.presentScene(scene)
    }

    override var shouldAutorotate : Bool {
        return true
    }

    override var supportedInterfaceOrientations : UIInterfaceOrientationMask {
        if UIDevice.current.userInterfaceIdiom == .phone {
            return UIInterfaceOrientationMask.allButUpsideDown
        } else {
            return UIInterfaceOrientationMask.all
        }
    }

    override var prefersStatusBarHidden : Bool {
        return true
    }
}
