//
//  ViewController.swift
//  Guess My Number
//
//  Created by Jeffrey Ryan on 2/10/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet var infoLabel: UILabel!
    @IBOutlet var inputField: UITextField!
    @IBOutlet var playButton: UIButton!
    
    var minNumber: Int = 1
    var maxNumber: Int = 1000000
    var betweenGames: Bool = true
    
    var targetNumber: Int = 0
    var numGuesses: Int = 0
    
    @IBAction func buttonPressed(sender: AnyObject) {
        if betweenGames {
            targetNumber = generateRandomNumber()
            infoLabel.text = "I am thinking of a number between \(minNumber) and \(maxNumber)"
            inputField.enabled = true
            playButton.setTitle("Guess", forState: UIControlState.Normal)
            betweenGames = false
        }
        else {
            var enteredNumber = inputField.text.toInt()
            
            if enteredNumber != nil {
                numGuesses++
                
                if enteredNumber! == targetNumber {
                    infoLabel.text = "\(targetNumber) is correct, it only took you \(numGuesses) guesses!"
                    inputField.enabled = false
                    playButton.setTitle("Restart", forState: UIControlState.Normal)
                    betweenGames = true
                }
                else if enteredNumber > targetNumber {
                    infoLabel.text = "\(enteredNumber!) is too high!"
                }
                else {
                    infoLabel.text = "\(enteredNumber!) is too low!"
                }
            }
        }
        
        inputField.text = ""
    }
    
    func generateRandomNumber() -> Int {
        var difference: Int! = maxNumber - minNumber
        
        return Int(arc4random_uniform(UInt32(difference))) + minNumber
    }
    
    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        infoLabel.text = "Welcome"
        inputField.enabled = false
        playButton.setTitle("Play!", forState: UIControlState.Normal)
    }
}

