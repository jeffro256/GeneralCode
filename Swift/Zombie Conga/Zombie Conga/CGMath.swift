//
//  CGMath.swift
//  Zombie Conga
//
//  Created by Jeffrey Ryan on 2/22/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import Foundation
import CoreGraphics

let π = CGFloat(M_PI)

func +(left: CGPoint, right: CGPoint) -> CGPoint {
    return CGPointMake(left.x + right.x, left.y + right.y)
}

func +(left: CGPoint, right: CGVector) -> CGPoint {
    return left + CGPoint(x: right.dx, y: right.dy)
}

func +=(inout left: CGPoint, right: CGPoint) {
    left = left + right
}

func +=(inout left: CGPoint, right: CGVector) {
    left = left + right
}

func -(left: CGPoint, right: CGPoint) -> CGPoint {
    return CGPointMake(left.x - right.x, left.y - right.y)
}

func -(left: CGPoint, right: CGVector) -> CGPoint {
    return left - CGPoint(x: right.dx, y: right.dy)
}

func -=(inout left: CGPoint, right: CGPoint) {
    left = left - right
}

func -=(inout left: CGPoint, right: CGVector) {
    left = left - right
}

func *(left: CGPoint, right: CGFloat) -> CGPoint {
    return CGPointMake(left.x * right, left.y * right)
}

func *(left: CGVector, right: CGFloat) -> CGVector {
    return CGVectorMake(left.dx * right, left.dy * right)
}

func *=(inout left: CGPoint, right: CGFloat) {
    left = left * right
}

func *=(inout left: CGVector, right: CGFloat) {
    left = left * right
}

func /(left: CGPoint, right: CGFloat) -> CGPoint {
    return CGPointMake(left.x / right, left.y / right)
}

func /(left: CGVector, right: CGFloat) -> CGVector {
    return CGVectorMake(left.dx / right, left.dy / right)
}

func /=(inout left: CGPoint, right: CGFloat) {
    left = left / right
}

func /=(inout left: CGVector, right: CGFloat) {
    left = left / right
}

func shortestAngleBetweenAngles(a1: CGFloat, a2: CGFloat) -> CGFloat {
    var radiansInCircle = π * 2
    var angle = (a2 - a1) % radiansInCircle
    
    if (angle >= π) {
        angle -= radiansInCircle
    }
    if (angle <= -π) {
        angle += radiansInCircle
    }

    return angle
}

extension CGFloat {
    func sign() -> CGFloat {
        return (self > 0) ? -1.0 : 1.0
    }
}

extension CGPoint {
    func length() -> CGFloat {
        return sqrt(x * x + y * y)
    }
}

extension CGVector {
    func length() -> CGFloat {
        return sqrt(dx * dx + dy * dy)
    }
}