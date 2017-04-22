//
//  SKSpriteNode+Extensions.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/23/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

extension SKSpriteNode {
    func sizeWithWidth(_ width: CGFloat) -> CGSize {
        return CGSize(width: width, height: width / self.size.width * self.size.height)
    }
    
    func sizeWithHeight(_ height: CGFloat) -> CGSize {
        return CGSize(width: height / self.size.height * self.size.width, height: height)
    }
    
    func resizeWithWidth(_ width: CGFloat) {
        self.size = self.sizeWithWidth(width)
    }
    
    func resizeWithHeight(_ height: CGFloat) {
        self.size = self.sizeWithHeight(height)
    }
    
    func sizeWithRatio(_ ratio: CGFloat) -> CGSize {
        return CGSize(width: self.size.width * ratio, height: self.size.height * ratio)
    }
    
    func resizeWithRatio(_ ratio: CGFloat) {
        self.size = self.sizeWithRatio(ratio)
    }
}
