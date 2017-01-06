//: Playground - noun: a place where people can play

import QuartzCore

var now = Date()
var future = Date(timeIntervalSinceNow: 100000)

print(now)
print(future)

print(DateComponents(calendar: Calendar.current, timeZone: TimeZone.current, era: 0, year: 2001, month: 5, day: 12, hour: 15, minute: 28, second: 42, nanosecond: 2))

var result = Calendar.current.compare(now, to: future, toGranularity: .day)

switch (result) {
case .orderedSame:
    print("same")
case .orderedAscending:
    print("more")
case .orderedDescending:
    print("less")
}

var a = [4, 3, 6, 5, 4, 0]
a.sort { $0 > $1 }
a

extension Date {
    var timeIntervalSinceDayStart: TimeInterval {
        let com = Calendar.current.dateComponents([.year, .month, .day], from: self)
        let dayStart = Calendar.current.date(from: com)

        return (self.timeIntervalSinceReferenceDate - dayStart!.timeIntervalSinceReferenceDate)
    }
}

let com = Calendar.current.dateComponents([.year, .month, .day], from: now)
let dayStart = Calendar.current.date(from: com)
now.timeIntervalSinceDayStart

let com2 = DateComponents(hour: 8, minute: 34)
let timeDate = Calendar.current.date(from: com2)
timeDate?.timeIntervalSinceDayStart
