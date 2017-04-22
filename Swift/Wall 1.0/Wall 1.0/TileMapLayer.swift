/*
 * Copyright (c) 2013-2014 Razeware LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

import SpriteKit

class TileMapLayer : SKNode {
  
  let tileSize: CGSize
  var atlas: SKTextureAtlas?
  let size: CGSize
  let layerSize: CGSize
  
  required init?(coder aDecoder: NSCoder) {
    fatalError("NSCoding not supported")
  }

  init(tileSize: CGSize, gridSize: CGSize,
      layerSize: CGSize? = nil) {
    self.tileSize = tileSize
    self.size = gridSize
    if layerSize != nil {
      self.layerSize = layerSize!
    } else {
      self.layerSize =
        CGSize(width: tileSize.width * gridSize.width,
               height: tileSize.height * gridSize.height)
    }
    super.init()
  }
  
  convenience init(atlasName: String, tileSize: CGSize,
    tileCodes: [[String]]) {
    self.init(tileSize: tileSize,
              gridSize: CGSize(width: count(tileCodes[0]),
              height: tileCodes.count))
    
    atlas = SKTextureAtlas(named: atlasName)
    
    /*enumerate(tileCodes) { rowNum, row in
        enumerate(row) { colNum, col in
            var tile = nodeForCode(col)
            tile.position = positionForRow(rowNum, colNum)
            
            self.addChild(
        }
    }*/
  }

  func nodeForCode(tileCode: Character) -> SKNode? {
    if atlas == nil {
      return nil
    }
    
    // remove later
    return nil
  }
  
  func positionForRow(row: Int, col: Int) -> CGPoint {
    let x = CGFloat(col) * tileSize.width + tileSize.width / 2
    let y = CGFloat(row) * tileSize.height + tileSize.height / 2
    return CGPoint(x: x, y: layerSize.height - y)
  }
  
  func isValidTileCoord(coord: CGPoint) -> Bool {
    return (
      coord.x >= 0 &&
      coord.y >= 0 &&
      coord.x < size.width &&
      coord.y < size.height)
  }
  
  func coordForPoint(point: CGPoint) -> CGPoint {
    return CGPoint(x: Int(point.x / tileSize.width),
                   y:Int((point.y - layerSize.height) / -tileSize.height))
  }
  
  func pointForCoord(coord: CGPoint) -> CGPoint {
    return positionForRow(Int(coord.y), col: Int(coord.x))
  }
  
  func tileAtCoord(coord: CGPoint) -> SKNode? {
    return tileAtPoint(pointForCoord(coord))
  }
  
  func tileAtPoint(point: CGPoint) -> SKNode? {
    var node : SKNode? = nodeAtPoint(point)
    while node !== self && node?.parent !== self {
      node = node?.parent
    }
    return node?.parent === self ? node : nil
  }
}

