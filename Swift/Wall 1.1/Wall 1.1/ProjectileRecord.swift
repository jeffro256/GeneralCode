//
//  ProjectileRecord.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/23/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import Foundation

struct ProjectileRecord {
    var velocity: CGVector
    var readyToShoot: Bool
    var timeSinceShot: TimeInterval
    var minTimeBetweenShots: TimeInterval
    
    init(velocity: CGVector, readyToShoot: Bool, lastShootTime: TimeInterval, minTimeBetweenShots: TimeInterval) {
        self.velocity = velocity
        self.readyToShoot = readyToShoot
        self.timeSinceShot = lastShootTime
        self.minTimeBetweenShots = minTimeBetweenShots
    }
    
    init(velocity: CGVector, readyToShoot: Bool, minTimeBetweenShots: TimeInterval) {
        self.init(velocity: velocity, readyToShoot: readyToShoot, lastShootTime: 0, minTimeBetweenShots: minTimeBetweenShots)
    }
    
    init(velocity: CGVector, minTimeBetweenShots: TimeInterval) {
        self.init(velocity: velocity, readyToShoot: false, lastShootTime: 0, minTimeBetweenShots: minTimeBetweenShots)
    }
    
    init(minTimeBetweenShots: TimeInterval) {
        self.init(velocity: CGVector(dx: 0, dy: 0), readyToShoot: false, lastShootTime: 0, minTimeBetweenShots: minTimeBetweenShots)
    }
}
