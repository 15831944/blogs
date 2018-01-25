//: Playground - noun: a place where people can play

import UIKit

// variable and constant
let maxNum = 100
var index = 5
// Int
var imInt = 80
Int.max
Int.min
var imUInt = 50
UInt.max
UInt.min
Int8.max
UInt8.max
Int16.min
Int32.max
Int64.max
let decimalInt = 17
let binaryInt = 0b10001
let octalInt = 0o21
let hexInt = 0x11
var bigInt = 1_000_000
// Float
let imFloat: Float = 0.123456789123456789
let imDouble = 0.123456789123456789
var a = 1.23456789e10
var b = 1.23e-10
var bigFloat = 1_000_000.000_1
let integer = 3
let fraction = 0.14
Double (integer) + fraction
let red: CGFloat = 0.8
let green: CGFloat = 0.5
let blue: CGFloat = 0.1
UIColor(red: red, green: green, blue: blue, alpha: 1.0)
// Bool
let imTrue = true
let imFalse = false
// String
var str: String = "20,30"
let comma = str.range(of: ",")!.lowerBound
let first = str.substring(to: comma)
let second = str.substring(from: comma)

// Struction
struct Location{
    var latitude: Double = 0					// 结构体成员默认值
    var longtitude: Double = 0
    var placeName: String?					// 可选型具有初值 nil
    
    init?(coordinateString: String){			// 构造函数
        guard let commaIndex = coordinateString.range(of: ",")?.lowerBound else{
            return nil
        }
        guard let firstElement = Double(coordinateString.substring(to: commaIndex)) else{
            return nil
        }
//       	guard let secondElement = Double(coordinateString.substring(from: commaIndex.successor())) else{
//            return nil
//        }
        self.latitude   = firstElement
//		self.longtitude = secondElement
    }
    
    init(latitude: Double, longtitude: Double) {
        self.latitude   = latitude
        self.longtitude = longtitude
    }
    
    init(latitude: Double, longtitude: Double, placeName: String) {
        self.latitude   = latitude
        self.longtitude = longtitude
        self.placeName  = placeName
    }

}
//Location()														// 不带参数的默认构造函数
let location1 = Location(latitude: 37.3230, longtitude: -122.0322)	// 参数完整的默认构造函数
let location2 = Location(coordinateString:"37.3230,-122.0322")		// 自定义构造函数
let location3 = Location(latitude: 37.3230, longtitude: -122.0322)
let location4 = Location(latitude: 37.3230, longtitude: -122.0322, placeName: "apple head quarter")









