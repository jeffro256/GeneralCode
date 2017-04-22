//
//  CGRect+Extensions.swift
//  Pogo 0.1
//
//  Created by Jeffrey Ryan on 5/21/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import CoreGraphics
import SpriteKit

extension CGRect {
    var center: CGPoint {
        return CGPoint(x: CGRectGetMidX(self), y: CGRectGetMidY(self))
    }
}