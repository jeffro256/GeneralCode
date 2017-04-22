//
//  MenuScene.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 5/6/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class MenuScene: SKScene {
    var playButton: SKSpriteNode!
    
    override init(size: CGSize) {
        super.init(size: size)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func didMove(to view: SKView) {
        let background = SKSpriteNode(imageNamed: "menu.png")
        background.name = "background"
        let oldWidth = background.size.width
        background.resizeWithWidth(self.frame.width)
        background.position = self.frame.center
        background.texture?.filteringMode = .nearest
        
        addChild(background)
        
        playButton = SKSpriteNode(imageNamed: "play_button")
        playButton.name = "play-button"
        playButton.position = self.frame.center
        playButton.zPosition = 20
        playButton.resizeWithWidth(background.size.width / oldWidth * playButton.size.width)
        playButton.texture?.filteringMode = .nearest
        
        addChild(playButton)
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        for touch in (touches ) {
            let touchLocation = touch.location(in: self)
            
            if playButton.contains(touchLocation) {
                let scene = GameScene(size: self.view!.bounds.size)
                view?.presentScene(scene)
                scene.run(Sounds.buster1)
            }
        }
    }
}
