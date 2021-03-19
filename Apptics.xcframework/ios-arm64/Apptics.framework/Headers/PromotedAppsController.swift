//
//  PromotedAppsController.swift
//
//
//  Created by Prakash R on 04/08/20.
//

import UIKit
import StoreKit

struct promotedDatasource {
    
    var appName : String
    var caption : String
    var imageUrl : String
    var appstoreUrl : String
    var appIdentifier : String
    var crossPromoAppId : Int
    var appInstallStatus : Bool
    var appscheme : String
    
}

@objcMembers
@objc public class PromotedAppsController: UIViewController, UITableViewDataSource, UITableViewDelegate, SKStoreProductViewControllerDelegate {
    
    @IBOutlet var tblView: UITableView!
    @IBOutlet var lblerrorMessage: UILabel!
    @IBOutlet var vwSuperView: UIView!
    @IBOutlet var viewAppapps: UIView!
    @IBOutlet var btnAllApps: UIButton!
    @IBOutlet var lblRightArrow: UILabel!
    @IBOutlet var lblViewAllApps: UILabel!
    @IBOutlet var lblAllAppsIcon: UILabel!
    
    var defaultTheme : APThemeSwift = APThemeSwift()
    var crossPromoTheme : CrossPromoTheme = CrossPromoTheme()
    var showAllAppsView : Bool = false
    var allAppsLink : String?
    var dataSource : [[promotedDatasource]] = []
    var promotionalApps : [promotedDatasource]?
    var otherApps : [promotedDatasource]?
    @objc public var delegate : PromotedAppsKitDelegate?
//    var bgColor : UIColor?
//    var lblColor :UIColor?
    var hasInternet : Bool = true
    var sectionLabel1 : String?
    var sectionLabel2 : String?
    var imageCornerRadius : Float?
    var isOtherAppsPresent : Bool = false
    var isPromotionalAppsPresent : Bool = false
//    var noData : Bool = false
    var isRefresh : Bool = false
    var spinner = UIActivityIndicatorView(style: .gray)
    
    
    public func loadScreenWith(AppsData: NSObject?, sectionHeader1: String?, sectionHeader2: String?) {
        
        
        if let apps = AppsData {
            
            self.sectionLabel1 = sectionHeader1
            self.sectionLabel2 = sectionHeader2
//
//        self.navigationController?.navigationBar.barTintColor = bgColor

        fillDataWith(info: apps)
        
        } else {
//            noData = true
            if isRefresh {
                checkAndUpdateScreenforNoData()
            }
        }
    }
    
    public override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: Bundle?) {
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
        
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    
    open override func viewDidLoad() {
        super.viewDidLoad()
        
        defaultTheme = APThemeSwiftManager.sharedTheme
        crossPromoTheme = APThemeSwiftManager.crosspromotheme
        
        let bundler = self.getcurrentBundle()
        
        
        tblView.register(UINib(nibName: "promotedAppViewCell", bundle: bundler), forCellReuseIdentifier: "zapromotedcell")
        
        lblerrorMessage.isHidden = false
        lblerrorMessage.text = "No Apps to display"
        lblAllAppsIcon.text = "\u{e916}"
        lblAllAppsIcon.font = UIFont(name: "icon", size: 32)
        lblRightArrow.text = "\u{e915}"
        lblRightArrow.font = UIFont(name: "icon", size: 22)
//        lblerrorMessage.textColor = lblColor
        tblView.isHidden = true
        tblView.delegate = self
//        tblView.contentInset.top = 100
        
        tblView.dataSource = self
        view.addSubview(spinner)
        
        spinner.hidesWhenStopped = true
        spinner.stopAnimating()
        spinner.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
        spinner.centerYAnchor.constraint(equalTo: view.centerYAnchor).isActive = true
        if dataSource.count == 0 && hasInternet {
            
//            noData = true
            checkAndUpdateScreenforNoData()
                    
        } else if dataSource.count == 0 && !hasInternet {
            
            self.lblerrorMessage.text = "No active internet connection"
            self.lblerrorMessage.isHidden = false
            self.tblView.isHidden = true
            
        } else {
                    self.lblerrorMessage.isHidden = true
                    self.tblView.isHidden = false
                    self.tblView.reloadData()
            }
        
        if showAllAppsView {
            viewAppapps.isHidden = false
        } else {
            viewAppapps.isHidden = true
        }
        applyTheme()
    }
    
    
    

    
    
    
    public override class func awakeFromNib() {
        super.awakeFromNib()
    }
    
    
    func applyTheme() {
        
        
        let bar = self.navigationController?.navigationBar
        
        
            if let tintcolor = crossPromoTheme.tintColor {
                lblerrorMessage.textColor = tintcolor
                bar?.tintColor = tintcolor
            } else if let defaulttintcolor = defaultTheme.tintColor {
                lblerrorMessage.textColor = defaulttintcolor
                bar?.tintColor = defaulttintcolor
            } else {
                lblerrorMessage.textColor = bar?.tintColor
            }
        
        
            if let bgColor = crossPromoTheme.viewBGColor {
                tblView.backgroundColor = bgColor
                vwSuperView.backgroundColor = bgColor
                viewAppapps.backgroundColor = bgColor.withAlphaComponent(0.8)
                
            }
            
        
        if let separatorColor = crossPromoTheme.tableViewSeparatorColor {
            tblView.separatorColor = separatorColor
        }
        
        if let bartintColor = crossPromoTheme.barTintColor {
            bar?.barTintColor = bartintColor
//        } else if let defaultBarTintColor = defaultTheme.barTintColor {
//            tblView.backgroundColor = defaultBarTintColor
//            vwSuperView.backgroundColor = defaultBarTintColor
//        } else {
//            tblView.backgroundColor = bar?.barTintColor
//            vwSuperView.backgroundColor = bar?.barTintColor
        }
            
        if let attributes = crossPromoTheme.titleTextAttributes {
            bar?.titleTextAttributes = attributes
        } else if let defaultAttributes = defaultTheme.titleTextAttributes {
            bar?.titleTextAttributes = defaultAttributes
        }
        
        if let translucent = crossPromoTheme.translucent {
            bar?.isTranslucent = translucent
        } else if let defaulttranslucent = defaultTheme.translucent {
            bar?.isTranslucent = defaulttranslucent
        }
            
        
        
    }
    
    func fillDataWith(info:NSObject) {
        
        
        self.isOtherAppsPresent = false
        self.isPromotionalAppsPresent = false
        spinner.stopAnimating()
        if let data = info as? [String:Any] {
            
        let apps = data
                if apps.isEmpty {
                    spinner.translatesAutoresizingMaskIntoConstraints = false
                    if getTraitColor() == UIColor.black {
                        spinner.color = .white
                    } else {
                        spinner.color = .gray
                    }
                    spinner.startAnimating()
                    
//                    noData = true
                    if isRefresh {
                        spinner.stopAnimating()
                        
                        self.checkAndUpdateScreenforNoData()
                    }
                    return
                }
                
                if let allAppsStatus = apps["familyappsstatus"] as? Int {
                    if allAppsStatus == 1 {
                        self.showAllAppsView = true
                        self.allAppsLink = apps["familyappslink"] as? String
                    } else {
                        self.showAllAppsView = false
                    }
                }
                if let promotedApps = apps["0"] as? [[String:Any]]{
                    self.promotionalApps = []
                    for app in promotedApps {
                        
                        let crossPromoId = app["crosspromoappid"] as? Int ?? 0
                        let bundleIdentifier = app["identifier"] as? String ?? ""
                        let scheme = app["urlschemes"] as? String ?? ""
                        var appname :String
                        var appicon :String
                        var caption :String
                        if let appinfo = app["appinfo"] as? [String:Any] {
                            
                            appname = appinfo["name"] as? String ?? ""
                            appicon = appinfo["appicon"] as? String ?? ""
                            caption = appinfo["description"] as? String ?? ""
                            
                            let status = self.getAppDownloadStatusFor(appScheme: scheme)
                            
                            let promotedAppData = promotedDatasource(appName: appname, caption: caption, imageUrl: appicon, appstoreUrl: "", appIdentifier: bundleIdentifier, crossPromoAppId: crossPromoId, appInstallStatus: status, appscheme: scheme)
                            
                            self.promotionalApps?.append(promotedAppData)
                        }
                        
                        
                    }
                    
                    if let promo = self.promotionalApps {
                        self.dataSource.append(promo)
                        self.isPromotionalAppsPresent = true
                    }
                    
                }
                
                if let otherApps = apps["1"] as? [[String:Any]]{
                    self.otherApps = []
                    for app in otherApps {
                        
                        let crossPromoId = app["crosspromoappid"] as? Int ?? 0
                        let bundleIdentifier = app["identifier"] as? String ?? ""
                        let scheme = app["urlschemes"] as? String ?? ""
                        var appname :String
                        var appicon :String
                        var caption :String
                        if let appinfo = app["appinfo"] as? [String:Any] {
                            appname = appinfo["name"] as? String ?? ""
                            appicon = appinfo["appicon"] as? String ?? ""
                            caption = appinfo["description"] as? String ?? ""
                            let status = self.getAppDownloadStatusFor(appScheme: scheme)
                            
                            let otherAppData = promotedDatasource(appName: appname, caption: caption, imageUrl: appicon, appstoreUrl: "", appIdentifier: bundleIdentifier, crossPromoAppId: crossPromoId, appInstallStatus: status, appscheme: scheme)
                            
                            self.otherApps?.append(otherAppData)
                        }
                        
                    }
               
                }
                if let others = self.otherApps {
                    self.dataSource.append(others)
                    self.isOtherAppsPresent = true
                }
            
        } else {
//            noData = true
        }
        if isRefresh {
            checkAndUpdateScreenforNoData()
        }
    }
    
    func checkAndUpdateScreenforNoData() {
        
        if dataSource.count == 0 {
            
                lblerrorMessage.isHidden = false
                lblerrorMessage.text = "No Apps to display"
                tblView.isHidden = true
//                lblerrorMessage.textColor = lblColor
            
        } else {
            
            self.lblerrorMessage.isHidden = true
            self.tblView.isHidden = false
            self.tblView.reloadData()
            
        }
        
        if showAllAppsView {
            viewAppapps.isHidden = false
        } else {
            viewAppapps.isHidden = true
        }
        
    }
    
    
    
    
    @IBAction func allAppsButtonPresed(_ sender: Any) {
        
        
//        https://apps.apple.com/in/developer/zoho-corporation/id388384807
        if let urlStr = self.allAppsLink {
        
        if let path = URL(string: urlStr) {                          
            self.delegate?.ap_openURL(url: path)
        }
        }
    }
    
    
    
    public func numberOfSections(in tableView: UITableView) -> Int {
        return dataSource.count
    }
    
    public func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        var int = 0
        
       int = dataSource[section].count

//        if int == 0 {
//            lblerrorMessage.text = "No Apps to display"
//            lblerrorMessage.isHidden = false
//            tblView.isHidden = true
//        }
        
        return int
    }
    
    public func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        //Did you register the cell with tableview?yeswhere ?
        let cell = tableView.dequeueReusableCell(withIdentifier: "zapromotedcell") as! PromotedAppViewCell
        
        cell.delegate = self
//        if let color = bgColor {
//
//            cell.vwSuperView.backgroundColor = color
//
//        }
        let navAppearance = self.navigationController?.navigationBar
        
        if let bgcolor = crossPromoTheme.cellBGColor {
            cell.vwSuperView.backgroundColor = bgcolor
        } else if let defaultbgcolor = defaultTheme.barTintColor {
            cell.vwSuperView.backgroundColor = defaultbgcolor
        } else {
            if let nav = navAppearance {
            cell.vwSuperView.backgroundColor = nav.barTintColor ?? UIColor.clear
            }
        }
        
        if let textColor = crossPromoTheme.cellTextColor {
            cell.lblAppName.textColor = textColor
            cell.lblCaption.textColor = textColor
            
        } else if let defaultTextColor = defaultTheme.tintColor {
            cell.lblAppName.textColor = defaultTextColor
            cell.lblCaption.textColor = defaultTextColor
            cell.appStatusButton.backgroundColor = defaultTextColor.withAlphaComponent(0.1)
        } else {
            if let nav = navAppearance {
            cell.lblAppName.textColor = nav.tintColor ?? UIColor.clear
            cell.lblCaption.textColor = nav.tintColor ?? UIColor.clear
            cell.appStatusButton.backgroundColor = nav.tintColor.withAlphaComponent(0.1)
            }
        }
        
        if let btnColor = crossPromoTheme.buttonBGColor {
            cell.appStatusButton.backgroundColor = btnColor
        } else if let defaultcolor = defaultTheme.tintColor {
            cell.appStatusButton.backgroundColor = defaultcolor.withAlphaComponent(0.1)
        } else if let nav = navAppearance {
                cell.appStatusButton.backgroundColor = nav.tintColor.withAlphaComponent(0.1)
            }
        
        if let font = crossPromoTheme.cellTextFont {
            cell.lblAppName.font = font
        }
        if let captionfont = crossPromoTheme.cellCaptionFont {
            cell.lblCaption.font = captionfont
        }
        
        cell.data = dataSource[indexPath.section][indexPath.row]

        cell.loadData()
        return cell
    }
    
    
    public func tableView(_ tableView: UITableView, viewForFooterInSection section: Int) -> UIView? {
        return UIView()
    }
    
    public func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        tableView.deselectRow(at: indexPath, animated: false)

        
    }
    
    public func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 50
    }
    
    
    
    public func tableView(_ tableView: UITableView, viewForHeaderInSection section: Int) -> UIView? {
        let navAppearance = self.navigationController?.navigationBar
        let returnedView = UIView(frame: CGRect(x: 0, y: 0, width: tableView.bounds.size.width, height: 50))
        if let bgcolor = crossPromoTheme.viewBGColor {
            returnedView.backgroundColor = bgcolor
        } else if let defaultbgcolor = defaultTheme.barTintColor {
            returnedView.backgroundColor = defaultbgcolor
        } else {
            returnedView.backgroundColor = navAppearance?.barTintColor
        }
       
        
        let line = UIView(frame: CGRect(x: 25, y: (returnedView.bounds.size.height - 1), width: tableView.bounds.size.width - 50, height: 0.75))
        
        
        
        if #available(iOS 13.0, *) {
            line.backgroundColor = UIColor.separator
        } else {
            line.backgroundColor = UIColor.init(red: 0.33, green: 0.33, blue: 0.35, alpha: 0.6)
        }
        
        let label = UILabel(frame: CGRect(x: 25, y: 15, width: tableView.bounds.size.width, height: 30))
        
        label.backgroundColor = UIColor.clear
        if dataSource.count == 2 {
            if (section == 0){
                
                if let sectionhead1 = sectionLabel1 {
                    label.text = sectionhead1
                } else {
                    label.text = "Apps that you may like"
                }
                
            }
            if (section == 1){
                if let sectionhead2 = sectionLabel2 {
                    label.text = sectionhead2
                } else {
                    label.text = "More apps from us"
                }
                
            }
        } else {
            if isPromotionalAppsPresent {
                if let sectionhead1 = sectionLabel1 {
                    label.text = sectionhead1
                } else {
                    label.text = "Apps that you may like"
                }
            } else if isOtherAppsPresent {
                
                if let sectionhead2 = sectionLabel2 {
                    label.text = sectionhead2
                } else {
                    label.text = "More apps from us"
                }
            }
            
        }
        
        if let sectionFont = crossPromoTheme.sectionHeaderFont {
            label.font = sectionFont
        } else {
            label.font = UIFont.preferredFont(forTextStyle: .title3)
            label.font = UIFont.boldSystemFont(ofSize: label.font.pointSize)
        }
        
        if let sectioncolor = crossPromoTheme.sectionHeaderTextColor {
            label.textColor = sectioncolor
        } else if let defaultcolor = defaultTheme.tintColor {
            label.textColor = defaultcolor
        } else {
            navAppearance?.barTintColor
        }
        
        returnedView.addSubview(line)
        returnedView.addSubview(label)
        
        return returnedView
    }
    
    
    func getAppDownloadStatusFor(appScheme:String) -> Bool {
        if let delegate = self.delegate{
            return delegate.ap_canOpenURL(url: URL(string: "\(appScheme)://app")!)
        }else{
            return false
        }            
    }
        
        
        
        func openStoreProductWithiTunesItemIdentifier(_ identifier: String) {
                
            guard let url = URL(string: "http://itunes.apple.com/lookup?bundleId=\(identifier)") else { return }
            do {
                spinner.startAnimating()
                let data = try Data(contentsOf: url)
                guard let json = try JSONSerialization.jsonObject(with: data, options: [.allowFragments]) as? [String: Any] else {
                    return
                }
                
                
                if let result = (json["results"] as? [Any])?.first as? [String: Any],
                    let id = result["trackId"] as? Int {
                    let storeViewController = SKStoreProductViewController()
                    storeViewController.delegate = self
                    spinner.stopAnimating()
                    let parameters = [ SKStoreProductParameterITunesItemIdentifier : String(describing: id)]
                    storeViewController.loadProduct(withParameters: parameters) { [weak self] (loaded, error) -> Void in
                        if loaded {
                            self?.present(storeViewController, animated: true, completion: nil)
                        }
                    }
                }
            } catch let erro as NSError {
                print(erro.description)
            }
        }
        
        
        func getTraitColor() -> UIColor {
            
            if #available(iOS 12.0, *) {
                if traitCollection.userInterfaceStyle == .dark {
                    return .black
                } else {
                    return .white
                }
            } else {
                return .white
            }
            
        }
        
        public override func traitCollectionDidChange(_ previousTraitCollection: UITraitCollection?) {
            self.applyTheme()
            self.tblView.reloadData()
        }
        
        
        func getcurrentBundle() -> Bundle {
            
            let bundle = Bundle(for: type(of: self))
            if let url = bundle.url(forResource: "AppticsResources", withExtension: "bundle") {
                if let bundl = Bundle.init(url: url) {
                    return bundl
                }
            }
            return bundle
        }
        
    }
    extension PromotedAppsController : PromotedAppViewCellDelegate {
        
        func appInstallBtnPressed(_ appScheme:String, _ crossPromoId:Int, _ identifier : String){
            
            if getAppDownloadStatusFor(appScheme: appScheme) {
                self.delegate?.promoAppselected(crossPromoId: NSNumber(value: crossPromoId), status: NSNumber(value: 1))
                self.delegate?.ap_openURL(url: URL(string: "\(appScheme)://")!)
            } else {
                self.delegate?.promoAppselected(crossPromoId: NSNumber(value: crossPromoId), status: NSNumber(value: 0))
                openStoreProductWithiTunesItemIdentifier(identifier)
            }
        }
    }

