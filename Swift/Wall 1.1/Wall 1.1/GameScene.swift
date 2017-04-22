//
//  GameScene.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 3/25/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

enum GameState {
    case playing, paused
}

class GameScene: SKScene, SKPhysicsContactDelegate {
    var map: JSTileMap?
    var mapSize: CGSize?
    var worldNode: SKNode!
    var player: Player!
    var healthBar: SKNode!
    var healthBarSize: CGSize!
    var enemyDisplay: SKNode!
    var maxEnemies: Int!
    var maxHealth: Double!
    var joystick: Joystick
    let joystickPadding: CGFloat = 50
    var lastTime: TimeInterval = 0
    var record: ProjectileRecord = ProjectileRecord(minTimeBetweenShots: 1)
    var boss: Boss!
    var pauseButton: SKSpriteNode = SKSpriteNode()
    var gameState: GameState
    var loaded = false

    override init(size: CGSize) {
        self.joystick = Joystick()
        self.gameState = GameState.playing
        
        super.init(size: size)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func didMove(to view: SKView) {
        if (!loaded) {
            createWorld()
            createPlayers()
            createOtherThings()
            updateHUD()

            loaded = true
        }
        
        worldNode.position = getCenterViewOn(player.position)
    }
    
    override func update(_ currentTime: TimeInterval) {
        if lastTime == 0 {
            lastTime = currentTime
        }
        
        let elapsedTime = currentTime - lastTime
        
        switch gameState {
        case .playing:
            if joystick.angularVelocity != 0.0 {
                let velocity = CGVector(dx: joystick.velocity.x, dy: joystick.velocity.y) / joystick.thumbNode.size.width * self.player.playerSpeed * CGFloat(elapsedTime)
                player.position += velocity
            }
        
            map?.enumerateChildNodes(withName: "Enemy") { node, _ in
                let enemy = node as! Enemy
            
                if !enemy.isDead {
                    let currentPos = enemy.position
                    let targetPos = self.player.position
                    let targetDist = CGVector(point: (targetPos - currentPos).normalized())
                    let velocity = targetDist * enemy.playerSpeed * CGFloat(elapsedTime)
                
                    if velocity.length() <= (targetPos - currentPos).length() {
                        enemy.position += velocity
                    }
                }
            }
            
            if getNumberOfLiveEnemies() <= 0 && boss.state == .notSpawned {
                spawnBoss()
            }
            
            if boss.isDead {
                self.view!.presentScene(GameOverScene(won: true, size: self.size))
            }
            
            if (player.health <= 0) {
                self.view?.presentScene(GameOverScene(won: false, size: self.size))
            }
        
            if record.readyToShoot && record.timeSinceShot >= record.minTimeBetweenShots {
                let busterAngle = atan2(record.velocity.dy, record.velocity.dx)
                let buster = Buster(angle: busterAngle, fromPlayer: self.player)
                
                worldNode.addChild(buster)
            
                record.timeSinceShot = 0
            }
        
            boss.step(elapsedTime)
            
            record.timeSinceShot += elapsedTime
            record.readyToShoot = false
        case .paused:
            break
        }
        
        lastTime = currentTime
    }
   
    override func didSimulatePhysics() {
        switch gameState {
        case .playing:
            let target = getCenterViewOn(player.position)
        
            worldNode.position += (target - worldNode.position) * 0.1
        case .paused:
            break
        }
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        for touch in (touches ) {
            switch gameState {
            case .playing:
                let touchInScreen = touch.location(in: self)
                
                if pauseButton.contains(touchInScreen) {
                    gameState = .paused
                    self.isPaused = true
                    pauseButton.isHidden = true
                    
                    let resumeButton = SKSpriteNode(imageNamed: "resume_button")
                    resumeButton.name = "resume-button"
                    resumeButton.resizeWithHeight(self.frame.height / 6)
                    resumeButton.texture?.filteringMode = .nearest
                    resumeButton.zPosition = 80
                    
                    let backButton = SKSpriteNode(imageNamed: "back_button")
                    backButton.name = "back-button"
                    backButton.resizeWithHeight(self.frame.height / 6)
                    backButton.texture?.filteringMode = .nearest
                    backButton.zPosition = 80
                    
                    resumeButton.position.y = resumeButton.size.height / 2 + 20
                    backButton.position.y = -backButton.size.height / 2 - 20
                    
                    addChild(resumeButton)
                    addChild(backButton)
                }
                else {
                    let touchLocation = touch.location(in: worldNode)
                    
                    let deltaX = touchLocation.x - self.player.position.x
                    let deltaY = touchLocation.y - self.player.position.y
                    
                    record.velocity = CGVector(dx: deltaX, dy: deltaY)
                    record.readyToShoot = true
                }
            case .paused:
                let touchLocation = touch.location(in: self)
                let playButton = self.childNode(withName: "resume-button")!
                let backButton = self.childNode(withName: "back-button")!
                
                if playButton.contains(touchLocation) {
                    gameState = .playing
                    self.isPaused = false
                    playButton.removeFromParent()
                    backButton.removeFromParent()
                    pauseButton.isHidden = false
                }
                else if backButton.contains(touchLocation) {
                    self.view?.presentScene(MenuScene(size: self.view!.bounds.size))
                }
            }
        }
    }
    
    func didBegin(_ contact: SKPhysicsContact) {
        if masksAreTouching(CollisionTypes.Player, mask2: CollisionTypes.Enemy, contact: contact) {
            player.health -= 1
            
            contact.bodyA.node?.run(Sounds.ghost1)
            
            updateHUD()
        }
        else if masksAreTouching(CollisionTypes.Buster, mask2: CollisionTypes.Enemy, contact: contact) {
            var enemy: Enemy
            if maskContainsSubmask(contact.bodyA.categoryBitMask, sub: CollisionTypes.Enemy) {
                enemy = contact.bodyA.node as! Enemy
            }
            else {
                enemy = contact.bodyB.node as! Enemy
            }
            
            contact.bodyA.node?.run(Sounds.buster1)
            
            boomFrom(enemy)
            killEnemy(enemy)
            updateHUD()
        }
        else if masksAreTouching(CollisionTypes.Buster, mask2: CollisionTypes.Block, contact: contact) || masksAreTouching(CollisionTypes.Buster, mask2: CollisionTypes.Boundary, contact: contact) {
            var buster: SKNode
            if maskContainsSubmask(contact.bodyA.categoryBitMask, sub: CollisionTypes.Buster) {
                buster = contact.bodyA.node!
            }
            else {
                buster = contact.bodyB.node!
            }
            buster.removeFromParent()
            
            boomFrom(buster)
        }
        else if masksAreTouching(CollisionTypes.Slime, mask2: CollisionTypes.Player, contact: contact) {
            player.health -= 1
            
            if maskContainsSubmask(contact.bodyA.categoryBitMask, sub: CollisionTypes.Slime) {
                contact.bodyA.node?.removeFromParent()
            }
            else {
                contact.bodyB.node?.removeFromParent()
            }
            
            updateHUD()
        }
        else if masksAreTouching(CollisionTypes.Player, mask2: CollisionTypes.Boss, contact: contact) {
            player.health -= 2
            
            contact.bodyA.node?.run(Sounds.ghost1)
            
            updateHUD()
        }
        else if masksAreTouching(CollisionTypes.Buster, mask2: CollisionTypes.Boss, contact: contact) {
            boss.health -= 1
            
            var buster: SKNode
            
            if maskContainsSubmask(contact.bodyA.categoryBitMask, sub: CollisionTypes.Buster) {
                buster = contact.bodyA.node!
            }
            else {
                buster = contact.bodyB.node!
            }
            
            buster.removeFromParent()
            boomFrom(buster)
            updateHUD()
        }
    }
    
    func getCenterViewOn(_ point: CGPoint) -> CGPoint {
        let x = point.x.clamped(mapSize!.width - self.frame.width / 2, self.frame.width / 2)
        let y = point.y.clamped(mapSize!.height - self.frame.height / 2, self.frame.height / 2)
        
        return CGPoint(x: -x, y: -y)
    }
    
    func createWorld() {
        self.anchorPoint = CGPoint(x: 0.5, y: 0.5)
        self.physicsWorld.gravity = CGVectorZero
        self.physicsWorld.contactDelegate = self
        
        worldNode = SKNode()

        map = JSTileMap(named: "maps/alpha1_2.tmx")
        createPhysicsBodiesForMap(map!)
        createObjectsForMap(map!)

        mapSize = CGSize(width: map!.mapSize.width * map!.tileSize.width, height: map!.mapSize.height * map!.tileSize.height)
        
        worldNode.addChild(map!)
        
        worldNode.physicsBody = SKPhysicsBody(edgeLoopFrom: CGRect(x: 0, y: 0, width: mapSize!.width, height: mapSize!.height))
        worldNode.physicsBody?.categoryBitMask = CollisionTypes.Boundary
        worldNode.physicsBody?.isDynamic = false
        worldNode.physicsBody?.friction = 0
        
        addChild(worldNode)
    }
    
    func createPlayers() {
        player = map!.childNode(withName: "Player") as! Player
    }
    
    func createOtherThings() {
        healthBar = SKNode()
        healthBar.position = CGPoint(x: self.frame.midX, y: -self.frame.height / 2 + 20)
        healthBar.zPosition = 60
        healthBar.xScale = 3
        healthBar.yScale = 3
        
        let red = SKSpriteNode(imageNamed: "bar0")
        let green = SKSpriteNode(imageNamed: "bar1")

        red.name = "red"
        green.name = "green"
        
        red.zPosition = 0
        green.zPosition = 20
        
        red.texture?.filteringMode = .nearest
        green.texture?.filteringMode = .nearest

        green.centerRect = CGRect(x: 1.0 / 62.0, y: 0.0 / 6.0, width: 60.0 / 62.0, height: 6.0 / 6.0)
        green.anchorPoint = CGPoint(x: 0, y: 0.5)
        healthBarSize = green.size
        green.position.x = -healthBarSize.width / 2
        
        healthBar.position.y += red.size.height / 2
        
        healthBar.addChild(red)
        healthBar.addChild(green)
        
        addChild(healthBar)
        
        joystick = Joystick()
        let joyX = -self.frame.width / 2 + joystick.size / 2 + joystickPadding
        let joyY = -self.frame.height / 2 + joystick.size / 2 + joystickPadding
        let joyZ: CGFloat = 60
        joystick.position = CGPoint(x: joyX, y: joyY)
        joystick.zPosition = joyZ
        self.addChild(joystick)
        
        enemyDisplay = SKNode()
        enemyDisplay.position = CGPoint(x: -self.frame.width / 2 + 20, y: self.frame.height / 2 - 20)
        enemyDisplay.zPosition = 80
        
        addChild(enemyDisplay)
        
        let enemyBack = SKSpriteNode(texture: SKTextureAtlas(named: "alpha_characters").textureNamed("ghost1"))
        enemyBack.name = "back"
        enemyBack.resizeWithHeight(self.frame.height / 6)
        enemyBack.position = CGPoint(x: enemyBack.size.width / 2, y: -enemyBack.size.height / 2)
        
        enemyDisplay.addChild(enemyBack)
        
        let enemyLabelBack = SKSpriteNode(color: UIColor.lightGray, size: CGSize(width: 65, height: 30))
        enemyLabelBack.name = "label_back"
        enemyLabelBack.position = CGPoint(x: enemyBack.position.x, y: enemyBack.position.y - enemyBack.size.height / 2 - enemyLabelBack.size.height / 2)
        enemyLabelBack.zPosition = 20
        
        enemyDisplay.addChild(enemyLabelBack)
        
        let enemyLabel = SKLabelNode(text: "<Update HUD>")
        enemyLabel.name = "enemy_label"
        enemyLabel.fontSize = 18
        enemyLabel.fontName = "American Typewriter"
        enemyLabel.verticalAlignmentMode = .center
        enemyLabel.horizontalAlignmentMode = .center
        enemyLabel.position = enemyLabelBack.position
        enemyLabel.zPosition = 40
        enemyLabel.fontColor = UIColor(red: 0.8, green: 0.05, blue: 0.05, alpha: 1.0)
        
        enemyDisplay.addChild(enemyLabel)
        
        maxEnemies = getNumberOfLiveEnemies()
        
        pauseButton = SKSpriteNode(imageNamed: "pause_button")
        pauseButton.name = "pause-button"
        pauseButton.texture?.filteringMode = .nearest
        pauseButton.resizeWithWidth(self.frame.width / 16)
        pauseButton.position = CGPoint(x: self.frame.width / 2 - pauseButton.size.width / 2 - 16, y: self.frame.height / 2 - pauseButton.size.height / 2 - 16)
        pauseButton.zPosition = 80
        
        addChild(pauseButton)
        
        self.boss = Boss(targetPlayer: self.player)
        self.maxHealth = player.health
    }
    
    func updateHUD() {
        let green = healthBar.childNode(withName: "green") as! SKSpriteNode
        let newScale = CGFloat(player.health / maxHealth)
        
        green.removeAction(forKey: "move")
        green.run(SKAction.scaleX(to: newScale, duration: 1.0 / 8.0), withKey: "move")
        
        let enemyLabel = enemyDisplay.childNode(withName: "enemy_label") as! SKLabelNode
        
        if boss.state != .notSpawned {
            enemyLabel.text = "\(Int(boss.health)) / \(Int(Boss.Health))"
        }
        else {
            enemyLabel.text = "\(getNumberOfLiveEnemies()) / \(maxEnemies!)"
        }
    }
    
    func getNumberOfLiveEnemies() -> Int {
        var numEnemies = 0
        self.map!.enumerateChildNodes(withName: "Enemy") { node, _ in
            let enemy = node as! Enemy
            
            if !enemy.isDead {
                numEnemies += 1
            }
        }
        
        return numEnemies
    }
    
    func killEnemy(_ enemy: Enemy) {
        let fadeOut = SKAction.sequence([SKAction.scaleX(to: 0, y: 0, duration: 1.0), SKAction.removeFromParent()])
        
        enemy.run(fadeOut)
        enemy.physicsBody = nil
        enemy.isDead = true
    }
    
    func boomFrom(_ node: SKNode) {
        let boomNode = SKSpriteNode(imageNamed: "boom0")
        boomNode.position = node.position
        boomNode.zPosition = node.zPosition + 1
        boomNode.size = CGSize(width: 60, height: 60)
        boomNode.run(SKAction.sequence([Animations.boom, SKAction.removeFromParent()]))
        
        worldNode.addChild(boomNode)
    }
    
    func spawnBoss() {
        boss.spawnIntoWorld(worldNode, distFromPlayer: 750)
        player.health = maxHealth
        
        enemyDisplay.removeFromParent()
        
        enemyDisplay = SKNode()
        enemyDisplay.position = CGPoint(x: -self.frame.width / 2 + 20, y: self.frame.height / 2 - 20)
        enemyDisplay.zPosition = 80
        
        addChild(enemyDisplay)
        
        let enemyBack = SKSpriteNode(imageNamed: "boss0")
        enemyBack.name = "back"
        enemyBack.resizeWithHeight(self.frame.height / 6)
        enemyBack.position = CGPoint(x: enemyBack.size.width / 2, y: -enemyBack.size.height / 2)
        enemyBack.run(Animations.boss)
        
        enemyDisplay.addChild(enemyBack)
        
        let enemyLabelBack = SKSpriteNode(color: UIColor.lightGray, size: CGSize(width: 65, height: 30))
        enemyLabelBack.name = "label_back"
        enemyLabelBack.position = CGPoint(x: enemyBack.position.x, y: enemyBack.position.y - enemyBack.size.height / 2 - enemyLabelBack.size.height / 2)
        enemyLabelBack.zPosition = 20
        
        enemyDisplay.addChild(enemyLabelBack)
        
        let enemyLabel = SKLabelNode(text: "<Update HUD>")
        enemyLabel.name = "enemy_label"
        enemyLabel.fontSize = 18
        enemyLabel.fontName = "American Typewriter"
        enemyLabel.verticalAlignmentMode = .center
        enemyLabel.horizontalAlignmentMode = .center
        enemyLabel.position = enemyLabelBack.position
        enemyLabel.zPosition = 40
        enemyLabel.fontColor = UIColor(red: 0.8, green: 0.05, blue: 0.05, alpha: 1.0)
        
        enemyDisplay.addChild(enemyLabel)
        
        updateHUD()
    }
}
