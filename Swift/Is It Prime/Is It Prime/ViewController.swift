//
//  ViewController.swift
//  Is It Prime
//
//  Created by Jeffrey Ryan on 2/11/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet var inputField: UITextField!
    @IBOutlet var resultLabel: UILabel!
    
    @IBAction func buttonPressed(sender: AnyObject) {
        var enteredNumber = inputField.text.toInt()
        
        if (enteredNumber != nil) {
            if isPrime(enteredNumber!) {
                resultLabel.text = "\(enteredNumber!) is prime"
            }
            else {
                resultLabel.text = "\(enteredNumber!) is not prime"
            }
        }
        else {
            resultLabel.text = ""
        }
        
        inputField.text = ""
    }
    
    func isPrime(num: Int) -> Bool {
        if num == 2 {
            return true
        }
        else if num < 2 {
            return false
        }
        
        let maxNum: Int = Int(ceil(sqrt(Double(num))))
        
        for i in 2...maxNum {
            if num % i == 0 {
                return false
            }
        }
        
        return true
    }
    
    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        resultLabel.text = ""
    }
}

