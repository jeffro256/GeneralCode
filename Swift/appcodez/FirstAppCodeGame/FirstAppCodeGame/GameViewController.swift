//
//  GameViewController.swift
//  FirstAppCodeGame
//
//  Created by Jeffrey Ryan on 4/17/15.
//  Copyright (c) 2015 Fish In Space. All rights reserved.
//

import UIKit
import SpriteKit

/*
extension SKNode {
    class func unarchiveFromFile(file : String) -> SKNode? {
        if let path = NSBundle.mainBundle().pathForResource(file, ofType: "sks") {
            var sceneData = NSData(contentsOfFile: path, options: .DataReadingMappedIfSafe, error: nil)!
            var archiver = NSKeyedUnarchiver(forReadingWithData: sceneData)
            
            archiver.setClass(self.classForKeyedUnarchiver(), forClassName: "SKScene")
            let scene = archiver.decodeObjectForKey(NSKeyedArchiveRootObjectKey) as! GameScene
            archiver.finishDecoding()
            return scene
        } else {
            return nil
        }
    }
}
*/

class GameViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()

        let scene = GameScene(size: self.view.bounds.size)
        let skView = self.view as! SKView

        skView.showsFPS = true
        skView.showsNodeCount = true
        skView.ignoresSiblingOrder = true
            
        scene.scaleMode = .AspectFill
            
        skView.presentScene(scene)
    }

    override func shouldAutorotate() -> Bool {
        return true
    }

    override func supportedInterfaceOrientations() -> Int {
        if UIDevice.currentDevice().userInterfaceIdiom == .Phone {
            return Int(UIInterfaceOrientationMask.Landscape.rawValue)
        } else {
            return Int(UIInterfaceOrientationMask.Landscape.rawValue)
        }
    }

    override func prefersStatusBarHidden() -> Bool {
        return true
    }
}
