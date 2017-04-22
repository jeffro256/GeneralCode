//
//  GameScene.swift
//  Doggo Dash
//
//  Created by Jeffrey Ryan on 1/8/16.
//  Copyright (c) 2016 Jeffrey Ryan. All rights reserved.
//

import SpriteKit

extension CGSize {
    public var aspectRatio: CGFloat {
        return width / height
    }
}

enum CollisionTypes {
    static let NONE:   UInt32 = 0
    static let ALL:    UInt32 = ~0
    static let DOGGO:  UInt32 = 1 << 1
    static let GROUND: UInt32 = 1 << 2
    static let MEME:   UInt32 = 1 << 3
    static let SCORE:  UInt32 = 1 << 4
}

class GameScene: SKScene, SKPhysicsContactDelegate {
    private let doggo = SKSpriteNode(imageNamed: "doggo")
    private let worldNode = SKNode()
    private let memeNode = SKNode()
    private let scoreLabel = SKLabelNode()
    private let resetButton = SKSpriteNode(imageNamed: "retry.jpeg")
    private let resetButtonSize: CGFloat = 40
    private let doggoScale: CGFloat = 0.28
    private let startSpeed: CGFloat = 13

    private var fingerDown = false
    private var bottomY: CGFloat!
    private var badMemeTextures: [SKTexture] = []
    private var score = 0
    private var memeSpeed: CGFloat = 0
    private var lastMemeTime: CFTimeInterval = 0
    private var jumping = false

    override func didMoveToView(view: SKView) {
        presetup()
        initBackground()
        initGround()
        initDoggo()
        initBadMemes()
        initUI()
    }
    
    override func touchesBegan(touches: Set<UITouch>, withEvent event: UIEvent?) {
        fingerDown = true

        if !worldNode.paused {

            if !jumping && !worldNode.paused {
                doggo.physicsBody?.applyImpulse(CGVectorMake(0, 120))
                jumping = true
            }
        }
        else {
            let touch = touches.first
            let location = touch!.locationInNode(self)

            if resetButton.containsPoint(location) {
                reset()
            }
        }
    }

    override func touchesEnded(touches: Set<UITouch>, withEvent event: UIEvent?) {
        fingerDown = false
    }
   
    override func update(currentTime: CFTimeInterval) {
        if fingerDown && doggo.position.y < 50 && doggo.physicsBody?.velocity.dy > 0 {
            doggo.physicsBody?.applyForce(CGVectorMake(0, 300))
        }

        if !worldNode.paused {
            memeSpeed = min(memeSpeed + 0.0025, 40)
        }

        let elapsed = CGFloat(currentTime - lastMemeTime)
        if lastMemeTime == 0 {
            lastMemeTime = currentTime
        }
        else if elapsed >= 20 / memeSpeed {
            spawnBadMeme()
            lastMemeTime = currentTime
        }
    }

    // SKPhysicsContactDelegate

    func didBeginContact(contact: SKPhysicsContact) {
        let bodyA = contact.bodyA
        let bodyB = contact.bodyB
        let nodeA = bodyA.node
        let nodeB = bodyB.node

        if nodeA?.name == "Doggo" && nodeB?.name == "Meme" {
            lose()
        }
        else if nodeB?.name == "Doggo" && nodeA?.name == "Meme"{
            lose()
        }
        else if nodeA?.name == "Doggo" && nodeB?.name == "Score" {
            score++
            updateHUD()
        }
        else if nodeB?.name == "Doggo" && nodeA?.name == "Score"{
            score++
            updateHUD()
        }
        else if nodeA?.name == "Doggo" && nodeB?.name == "Ground" {
            jumping = false
        }
        else if nodeB?.name == "Doggo" && nodeA?.name == "Ground" {
            jumping = false
        }
    }

    // New methods A-Z order

    func initBackground() {
        let backTexture = SKTexture(imageNamed: "doggo_back")
        let backRatio = backTexture.size().aspectRatio
        let backHeight = self.frame.height
        let backWidth = backHeight * backRatio
        let numBacks = Int(self.frame.width / backWidth) + 2

        let backgrounds = SKNode()
        backgrounds.position.x = -self.frame.width / 2
        backgrounds.zPosition = -20

        for var i = 0; i < numBacks; i++ {
            let backNode = SKSpriteNode(texture: backTexture)
            backNode.size = CGSizeMake(backWidth, backHeight)
            backNode.position.x = CGFloat(i) * backWidth + backWidth / 2

            backgrounds.addChild(backNode)
        }

        let moveLeft = SKAction.moveByX(-backWidth, y: 0, duration: 5)
        let moveBack = SKAction.moveByX(backWidth, y: 0, duration: 0)
        let moveSeq = SKAction.sequence([moveLeft, moveBack])
        let backAction = SKAction.repeatActionForever(moveSeq)

        backgrounds.runAction(backAction)

        worldNode.addChild(backgrounds)
    }

    func initBadMemes() {
        var badMemeNames = ["Deal_With_It", "Pepe", "bfrog.jpg", "deal_kid.gif", "doritos", "fwp", "gangnum", "john-cena", "kk.jpg", "ray_sipe", "redneck.jpeg", "sourtellingme.jpeg", "success.jpg", "thatdbe.jpg", "troll", "whynot.jpeg"]

        for (index, memeName) in badMemeNames.enumerate() {
            badMemeNames[index] = "Memes/" + memeName
        }

        for badMemeName in badMemeNames {
            badMemeTextures.append(SKTexture(imageNamed: badMemeName))
        }

        memeSpeed = startSpeed
        worldNode.addChild(memeNode)
    }

    func initDoggo() {
        doggo.name = "Doggo"
        doggo.position.x = -self.frame.width / 3
        doggo.position.y = bottomY
        doggo.zPosition = 20
        doggo.xScale = doggoScale
        doggo.yScale = doggoScale
        let doggoBodySize = CGSizeMake(doggo.size.width * 0.75, doggo.size.height)
        doggo.physicsBody = SKPhysicsBody(rectangleOfSize: doggoBodySize)
        doggo.physicsBody?.allowsRotation = false
        doggo.physicsBody?.categoryBitMask = CollisionTypes.DOGGO
        doggo.physicsBody?.collisionBitMask = CollisionTypes.GROUND
        doggo.physicsBody?.contactTestBitMask = CollisionTypes.MEME | CollisionTypes.GROUND
        doggo.physicsBody?.dynamic = true
        doggo.physicsBody?.restitution = 0
        doggo.physicsBody?.mass = 0.25

        self.addChild(doggo)
    }

    func initGround() {
        let groundThickness: CGFloat = 50
        bottomY = -self.frame.height / 2 + groundThickness

        let groundSize = CGSizeMake(self.frame.width, groundThickness)
        let groundColor = UIColor(colorLiteralRed: 1.0 / 255.0, green: 114.0 / 255.0, blue: 68.0 / 255.0, alpha: 1.0)
        let ground = SKSpriteNode(color: groundColor, size: groundSize)
        ground.name = "Ground"
        ground.physicsBody = SKPhysicsBody(rectangleOfSize: ground.size)
        ground.position = CGPointMake(0, bottomY - groundThickness / 2)
        ground.physicsBody?.allowsRotation = false
        ground.physicsBody?.categoryBitMask = CollisionTypes.GROUND
        ground.physicsBody?.collisionBitMask = CollisionTypes.DOGGO
        ground.physicsBody?.contactTestBitMask = CollisionTypes.DOGGO
        ground.physicsBody?.dynamic = false
        ground.physicsBody?.restitution = 0

        worldNode.addChild(ground)
    }

    func initUI() {
        let resetButtonRatio = resetButton.size.aspectRatio
        resetButton.size.width = self.frame.width / 3.5
        resetButton.size.height = resetButton.size.width / resetButtonRatio

        scoreLabel.position.y = self.frame.height / 3
        scoreLabel.fontSize = 40
        self.addChild(scoreLabel)
        updateHUD()
    }

    func lose() {
        if !worldNode.paused {
            worldNode.paused = true

            let rollOver = SKAction.scaleYTo(doggoScale * -1, duration: 0.5)
            doggo.runAction(rollOver)

            self.addChild(resetButton)
        }
    }

    func presetup() {
        self.anchorPoint = CGPointMake(0.5, 0.5)
        self.physicsWorld.gravity = CGVectorMake(0.0, -9.8)
        self.physicsWorld.contactDelegate = self

        self.addChild(worldNode)
    }

    func reset() {
        memeNode.removeAllChildren()
        memeNode.position.x = 0
        doggo.removeAllActions()
        doggo.yScale = doggoScale
        resetButton.removeFromParent()
        score = 0
        memeSpeed = startSpeed
        updateHUD()
        worldNode.paused = false
        jumping = false
    }

    func spawnBadMeme() {
        if worldNode.paused { return }

        let choice = Int(arc4random_uniform(UInt32(badMemeTextures.count)))
        let texture = badMemeTextures[choice]

        let badMemeEnemy = SKSpriteNode(texture: texture)
        badMemeEnemy.name = "Meme"
        let texAspectRatio = texture.size().aspectRatio
        badMemeEnemy.size.height = self.frame.height / 6
        badMemeEnemy.size.width = badMemeEnemy.size.height * texAspectRatio
        badMemeEnemy.position.x = self.frame.width / 2 + badMemeEnemy.size.width / 2
        badMemeEnemy.position.y = bottomY + badMemeEnemy.size.height / 2

        badMemeEnemy.physicsBody = SKPhysicsBody(rectangleOfSize: badMemeEnemy.size)
        badMemeEnemy.physicsBody?.dynamic = false
        badMemeEnemy.physicsBody?.categoryBitMask = CollisionTypes.MEME
        badMemeEnemy.physicsBody?.collisionBitMask = CollisionTypes.NONE
        badMemeEnemy.physicsBody?.contactTestBitMask = CollisionTypes.DOGGO

        let scoreNode = SKNode()
        scoreNode.name = "Score"
        let scoreSize = CGSizeMake(badMemeEnemy.size.width, self.frame.height / 2 - bottomY)
        scoreNode.physicsBody = SKPhysicsBody(rectangleOfSize: scoreSize)
        scoreNode.physicsBody?.dynamic = false
        scoreNode.physicsBody?.categoryBitMask = CollisionTypes.SCORE
        scoreNode.physicsBody?.collisionBitMask = CollisionTypes.NONE
        scoreNode.physicsBody?.contactTestBitMask = CollisionTypes.DOGGO

        scoreNode.position.x = badMemeEnemy.position.x
        scoreNode.position.y = badMemeEnemy.position.y + badMemeEnemy.size.height / 2 + scoreSize.height / 2

        let move = SKAction.moveByX(-self.frame.width - badMemeEnemy.size.width, y: 0, duration: NSTimeInterval(40 / memeSpeed))
        let die = SKAction.removeFromParent()
        let memeAction = SKAction.sequence([move, die])

        memeNode.addChild(badMemeEnemy)
        memeNode.addChild(scoreNode)
        badMemeEnemy.runAction(memeAction)
        scoreNode.runAction(memeAction)
    }

    func updateHUD() {
        scoreLabel.text = "\(score)"
    }
}