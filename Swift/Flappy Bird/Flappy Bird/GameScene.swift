//
//  GameScene.swift
//  Flappy Bird
//
//  Created by Jeffrey Ryan on 2/11/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

struct FlappyConstants {
    static let birdWidth = 84
    static let birdHeight = 60
    static let spaceBetweenPipes = birdHeight * 4
    
    static let CHARACTER_BITMASK: UInt32 = 1
    static let PIPE_BITMASK: UInt32 = 2
    static let GROUND_BITMASK: UInt32 = 4
    static let GAP_BITMASK: UInt32 = 8
}

class GameScene: SKScene, SKPhysicsContactDelegate {
    var bird = SKSpriteNode()
    var movingObjects = SKNode()
    var scoreLabel = SKLabelNode()
    var gameOverLabel = SKLabelNode()
    var gameOver = 0
    var score = 0
    
    func didBeginContact(contact: SKPhysicsContact) {
        if contact.bodyA.categoryBitMask == FlappyConstants.GAP_BITMASK || contact.bodyB.categoryBitMask == FlappyConstants.GAP_BITMASK {
            score++
            
            scoreLabel.text = "\(score)"
        }
        else {
            self.gameOver = 1
            self.movingObjects.speed = 0
            
            self.gameOverLabel.text = "Game Over"
        }
    }
    
    override func didMoveToView(view: SKView) {
        self.physicsWorld.contactDelegate = self
        //self.physicsWorld.gravity = CGVector(dx: 0, dy: -5)
        self.addChild(movingObjects)
        
        // add backgrounds
        self.moveBackgrounds()
        // add ground sprite
        let ground = SKNode()
        let groundHeight = 30
        ground.position = CGPoint(x: 0, y: -groundHeight / 2)
        ground.physicsBody = SKPhysicsBody(rectangleOfSize: CGSize(width: self.frame.width, height: CGFloat(groundHeight)))
        ground.physicsBody?.dynamic = false
        ground.physicsBody?.categoryBitMask = FlappyConstants.GROUND_BITMASK
        
        self.addChild(ground)
        // start adding bird sprite
        let birdTexture = SKTexture(imageNamed: "img/flappy1.png")
        let birdTexture2 = SKTexture(imageNamed: "img/flappy2.png")
        
        let animation = SKAction.animateWithTextures([birdTexture, birdTexture2], timePerFrame: 0.33)
        let flapAction = SKAction.repeatActionForever(animation)

        bird = SKSpriteNode(texture: birdTexture)
        bird.position = CGPoint(x: CGRectGetMidX(self.frame), y: self.frame.height)
        bird.zPosition = 1
        bird.runAction(flapAction)

        bird.physicsBody = SKPhysicsBody(circleOfRadius: bird.size.width / 2)
        bird.physicsBody?.dynamic = true
        bird.physicsBody?.allowsRotation = false
        bird.physicsBody?.categoryBitMask = FlappyConstants.CHARACTER_BITMASK
        bird.physicsBody?.collisionBitMask = FlappyConstants.PIPE_BITMASK | FlappyConstants.GROUND_BITMASK
        bird.physicsBody?.contactTestBitMask = FlappyConstants.PIPE_BITMASK | FlappyConstants.GROUND_BITMASK | FlappyConstants.GAP_BITMASK

        self.addChild(bird)
        // add score label
        scoreLabel.position = CGPoint(x: CGRectGetMidX(self.frame), y: self.frame.height - 75)
        scoreLabel.zPosition = 2
        
        scoreLabel.fontSize = 60
        
        self.addChild(scoreLabel)
        // setup game over label
        gameOverLabel.position = CGPoint(x: CGRectGetMidX(self.frame), y: CGRectGetMidY(self.frame))
        gameOverLabel.fontSize = 80
        gameOverLabel.fontColor = UIColor.redColor()
        
        self.addChild(gameOverLabel)
        // add pipe timer
        NSTimer.scheduledTimerWithTimeInterval(2, target: self, selector: Selector("spawnPipePair"), userInfo: nil, repeats: true)

        print("bird mass: \(bird.physicsBody?.mass)")
    }
    
    func generateRandomPipeHeight() -> Int {
        let topPadding = 20
        let bottomPadding = 20
        
        let minHeight = bottomPadding + FlappyConstants.spaceBetweenPipes / 2
        let maxHeight = Int(self.frame.height) - topPadding - FlappyConstants.spaceBetweenPipes / 2
        let diff = maxHeight - minHeight
        
        return Int(arc4random_uniform(UInt32(diff))) + minHeight
    }
    
    func moveBackgrounds() {
        let bgTexture = SKTexture(imageNamed: "img/bg.png")
        let bgWidth = bgTexture.size().width
        let numBackgrounds: Int = Int(ceil(max(self.frame.width, self.frame.height) / bgWidth)) + 1
        
        let movement = SKAction.moveByX(-bgWidth, y: 0, duration: 18)
        let moveBack = SKAction.moveByX(bgWidth, y: 0, duration: 0)
        let bgMoveAction = SKAction.repeatActionForever(SKAction.sequence([movement, moveBack]))
        
        for var i = 0; i < numBackgrounds; i++ {
            let bg = SKSpriteNode(texture: bgTexture)
            bg.position = CGPoint(x: bgWidth / 2 + bgWidth * CGFloat(i), y: CGRectGetMidY(self.frame))
            bg.size.height = self.frame.height
            bg.runAction(bgMoveAction)
            
            movingObjects.addChild(bg)
        }
    }
    
    func spawnPipePair() {
        // spawn a pipe pair that moves left and has physics body if the game isnt over
        if gameOver == 0 {
            let pipeTexture1 = SKTexture(imageNamed: "img/pipe1")
            let pipeTexture2 = SKTexture(imageNamed: "img/pipe2")
            let pipeWidth = 100
            let randomPipeHeight = generateRandomPipeHeight()
            let movePipe = SKAction.moveByX(-self.frame.width, y: 0, duration: 6)
            let removePipe = SKAction.removeFromParent()
            let moveAndRemovePipe = SKAction.sequence([movePipe, removePipe])
            
            let pipe1 = SKSpriteNode(texture: pipeTexture1)
            let pipe2 = SKSpriteNode(texture: pipeTexture2)
            let gap = SKNode()
            
            pipe1.position = CGPoint(x: self.frame.width, y: CGFloat(randomPipeHeight) + (pipe1.size.height / 2) + CGFloat(FlappyConstants.spaceBetweenPipes / 2))
            pipe2.position = CGPoint(x: self.frame.width, y: CGFloat(randomPipeHeight) - (pipe1.size.height / 2) - CGFloat(FlappyConstants.spaceBetweenPipes / 2))
            gap.position = CGPoint(x: self.frame.width, y: CGFloat(randomPipeHeight))
            
            pipe1.size.width = CGFloat(pipeWidth)
            pipe2.size.width = CGFloat(pipeWidth)
            
            pipe1.physicsBody = SKPhysicsBody(rectangleOfSize: pipe1.size)
            pipe2.physicsBody = SKPhysicsBody(rectangleOfSize: pipe2.size)
            gap.physicsBody = SKPhysicsBody(rectangleOfSize: CGSize(width: pipeWidth, height: FlappyConstants.spaceBetweenPipes))
            
            pipe1.physicsBody?.dynamic = false
            pipe2.physicsBody?.dynamic = false
            gap.physicsBody?.dynamic = false
            
            pipe1.physicsBody?.categoryBitMask = FlappyConstants.PIPE_BITMASK
            pipe2.physicsBody?.categoryBitMask = FlappyConstants.PIPE_BITMASK
            gap.physicsBody?.categoryBitMask = FlappyConstants.GAP_BITMASK
            
            pipe1.runAction(moveAndRemovePipe)
            pipe2.runAction(moveAndRemovePipe)
            gap.runAction(moveAndRemovePipe)
            
            movingObjects.addChild(pipe1)
            movingObjects.addChild(pipe2)
            movingObjects.addChild(gap)
        }
    }
    
    override func touchesBegan(touches: Set<UITouch>, withEvent event: UIEvent?) {
        if gameOver == 0 {
            bird.physicsBody?.velocity.dy = 0
            bird.physicsBody?.applyImpulse(CGVector(dx: 0, dy: 125))
        }
        else {
            score = 0
            scoreLabel.text = ""
            gameOverLabel.text = ""
            
            movingObjects.removeAllChildren()
            moveBackgrounds()
            movingObjects.speed = 1
            
            bird.position = CGPoint(x: CGRectGetMidX(self.frame), y: self.frame.height)
            bird.physicsBody?.velocity = CGVector(dx: 0, dy: 0)
            
            gameOver = 0
        }
    }
   
    override func update(currentTime: CFTimeInterval) {
        // this is called evry render
    }
}
