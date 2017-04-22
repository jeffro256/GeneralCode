//
//  GameOverScene.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/14/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class GameOverScene: SKScene {
    var restartButton = SKSpriteNode(imageNamed: "restart_button")
    var backButton = SKSpriteNode(imageNamed: "back_button")
    var won: Bool
    
    init(won: Bool, size: CGSize) {
        self.won = won
        
        super.init(size: size);
        
        setup()
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func setup() {
        let padding = CGSize(width: 20, height: 60)
        
        restartButton.resizeWithHeight(self.frame.height / 6)
        restartButton.texture?.filteringMode = .nearest
        
        backButton.resizeWithHeight(self.frame.height / 6)
        backButton.texture?.filteringMode = .nearest
        
        let widthDiff = restartButton.size.width - backButton.size.width
        restartButton.position = CGPoint(x: self.frame.width / 2 - restartButton.size.width / 2 - padding.width / 2 + widthDiff / 2, y: self.frame.height / 2 - restartButton.size.height / 2 - padding.height / 2)
        backButton.position = CGPoint(x: self.frame.width / 2 + backButton.size.width / 2 + padding.width / 2 + widthDiff / 2, y: self.frame.height / 2 - backButton.size.height / 2 - padding.height / 2)
        
        addChild(restartButton)
        addChild(backButton)
        
        let text = won ? "You Win!" : "Game Over" // frick you stephen
        let labelNode = SKLabelNode(text: text)
        labelNode.verticalAlignmentMode = .bottom
        labelNode.position = CGPoint(x: self.frame.width / 2, y: restartButton.position.y + restartButton.size.height / 2 + padding.height / 2)
        labelNode.fontSize = 60
        
        addChild(labelNode)
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        for touch in (touches ) {
            let touchLocation = touch.location(in: self)
            
            if restartButton.contains(touchLocation) {
                self.view?.presentScene(GameScene(size: self.view!.bounds.size))
            }
            else if backButton.contains(touchLocation) {
                self.view?.presentScene(MenuScene(size: self.view!.bounds.size))
            }
        }
    }
}
