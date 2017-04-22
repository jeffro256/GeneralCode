//
//  LoadTileMap.swift
//  Wall Jam
//
//  Created by Jeffrey Ryan on 2/26/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import Foundation
import CoreGraphics

/*
func loadTileMap(fileName: String) -> TileMapLayer? {
    let path = NSBundle.mainBundle().pathForResource(fileName, ofType: nil)
    
    if path == nil {
        println("bad path")
        return nil
    }
    
    var error: NSError?
    let fileContents = String(contentsOfFile: path!, encoding: NSUTF8StringEncoding, error: &error)
    
    if error != nil && fileContents == nil {
        return nil
    }
    
    let lines = fileContents!.componentsSeparatedByString("\n")
    let atlasName = lines[0]
    let tileSizeComps = lines[1].componentsSeparatedByString("x")
    let width = tileSizeComps[0].toInt()
    let height = tileSizeComps[1].toInt()
    
    if width != nil && height != nil {
        let tileSize = CGSize(width: width!, height: height!)
        
        var aliasDict = [String: String]()
        var lineNum = 2
        var line = lines[lineNum]
        
        while line != "end" {
            let keyAndVal = line.componentsSeparatedByString(" ")
            let key: String = keyAndVal[0]
            let val = keyAndVal[1]
            
            aliasDict[key] = val
            
            line = lines[++lineNum]
        }
        lineNum++
        
        let tileLines = lines[lineNum ..< lines.endIndex]
        
        var tileCodes = [[String]]() // constructor
        
        for row in tileLines {
            var rowCodes: [String]
            rowCodes = row.componentsSeparatedByString(" ")
            
            for (index, tile) in enumerate(rowCodes) {
                if let replacement = aliasDict[tile] {
                    rowCodes[index] = replacement
                }
            }
            
            tileCodes.append(rowCodes)
        }
        
        return TileMapLayer(atlasName: atlasName, tileSize: tileSize, tileCodes: tileCodes)
    }
    
    return nil
}*/
