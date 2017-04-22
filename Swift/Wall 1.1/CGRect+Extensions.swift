//
//  CGRect+Extensions.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/14/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

extension CGRect {
    var center: CGPoint {
        return CGPoint(x: self.midX, y: self.midY)
    }
}
