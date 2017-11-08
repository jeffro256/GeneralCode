//: Playground - noun: a place where people can play

import Foundation

func main() {
    URLCache.shared = URLCache(memoryCapacity: 0, diskCapacity: 0, diskPath: nil)

    let menu_url = URL(string: "http://sagedining.com/intranet/apps/mb/pubasynchhandler.php?unitId=S0025&mbMenuCardinality=2")!
    guard let data = try? Data(contentsOf: menu_url) else { print("Failed to get data"); return }
    guard let jsonObject = try? JSONSerialization.jsonObject(with: data, options: []) else { print("Failed to parse data"); return }

    let w = 2
    let d = 4
    let cm = 1
    let stationNames = [ "Stock Exchange", "Improvisations",
                       "ClassiczCuts", "Main Ingredient", "Seasonings", "Crossroads",
                       "Mangia, Mangia", "Transit Fare", "Baltimore Baking Co.",
                       "Splashes", "Variable", "Paquito's", "Pacific Thyme", "Vegitas" ]
    let stations = [ 3, 1, 5, 4, 0 ]

    guard let jsonDict = jsonObject as? [String: Any] else { return }
    guard let menu1 = jsonDict["menu"] as? [String: Any] else { return }
    guard let menu2 = menu1["menu"] as? [String: Any] else { return }
    guard let items = menu2["items"] as? [Any] else { return }
    guard let week = items[w] as? [Any] else { return }
    guard let day = week[d] as? [Any] else { return }
    guard let meal = day[cm] as? [Any] else { return }
    guard let menuBase = menu2["base"] as? [String: Any] else { return }

    guard let menuName = menuBase["name"] as? String else { return }
    print(menuName)

    for station in stations {
        print("-----------\(stationNames[station])-----------")
        guard let stationItems = meal[station] as? [Any] else { continue }
        for item in 0..<stationItems.count {
            guard let itemInfo = stationItems[item] as? [String: Any] else { continue }
            guard let itemName = itemInfo["t"] as? String else { continue }
            print(itemName)
        }
    }
}

main()