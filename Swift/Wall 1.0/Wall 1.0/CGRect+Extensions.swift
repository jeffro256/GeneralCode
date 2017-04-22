//
//  CGRect+Extensions.swift
//  Wall Jam
//
//  Created by Jeffrey Ryan on 2/26/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import CoreGraphics

extension CGRect {
    var center: CGPoint {
        return CGPointMake(CGRectGetMidX(self), CGRectGetMidY(self))
    }
}
