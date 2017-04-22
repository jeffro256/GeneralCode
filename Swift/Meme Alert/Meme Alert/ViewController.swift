//
//  ViewController.swift
//  Meme Alert
//
//  Created by Jeffrey Ryan on 2/11/16.
//  Copyright © 2016 Jeffrey Ryan. All rights reserved.
//

import UIKit
import AVFoundation

class ViewController: UIViewController {
    var soundID: SystemSoundID = 0

    override func viewDidLoad() {
        super.viewDidLoad()

        if let soundURL = NSBundle.mainBundle().URLForResource("dead_meme", withExtension: "wav") {
            AudioServicesCreateSystemSoundID(soundURL, &soundID)
        }
    }

    @IBAction func buttonPressed(sender: AnyObject) {
        AudioServicesPlaySystemSound(soundID);
    }

    override func supportedInterfaceOrientations() -> UIInterfaceOrientationMask {
        return .Portrait;
    }
}