//
//  TableViewCell.swift
//  Pods
//
//  Created by Prakash R on 04/08/20.
//

import UIKit


protocol PromotedAppViewCellDelegate {
    
    func appInstallBtnPressed(_ appScheme:String, _ crossPromoId:Int , _ identifier : String)
    
}


@objcMembers
@objc public class PromotedAppViewCell: UITableViewCell {

    @IBOutlet var imgIconn: CustomImageView!
    @IBOutlet var lblAppName: UILabel!
    @IBOutlet var lblCaption: UILabel!
    @IBOutlet var vwSuperView: UIView!
    @IBOutlet var appStatusButton: UIButton!
    
    
    var data : promotedDatasource?
    var delegate : PromotedAppViewCellDelegate?
    
    var appInstallStatus : Bool = false
   
    
    public override func awakeFromNib() {
        super.awakeFromNib()
     
        appStatusButton.titleLabel?.textAlignment = .center
        if let size = appStatusButton.titleLabel?.font.pointSize {
            appStatusButton.titleLabel?.font = UIFont.boldSystemFont(ofSize: size)
        }
        appStatusButton.layer.cornerRadius = 15
        
        
        
    }
    
    func loadData() {
        
                lblAppName.text = data?.appName
               lblCaption.text = data?.caption
        if let status = data?.appInstallStatus {
            appInstallStatus = status
        }
        
        appStatusButton.titleEdgeInsets = UIEdgeInsets.init(top: 0, left: 0, bottom: 0, right: 0)
        if appInstallStatus == true {
            appStatusButton.setTitle("OPEN", for: .normal)
        } else {
            appStatusButton.setTitle("GET", for: .normal)
        }
        
    
        
        
        if let uri = URL(string: data?.imageUrl ?? "") {
            
             imgIconn.downloadImageFrom(url: uri)
            imgIconn.layer.cornerRadius = 16
        }
       
    }
    
    
    @IBAction func appInstallPressed(_ sender: UIButton) {
        
        
        if let str = data?.appscheme {
            if let id = data?.crossPromoAppId, let identifier = data?.appIdentifier {
                
            
            self.delegate?.appInstallBtnPressed(str,id,identifier)
            }
        }
        
    }
    
    
    public override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
}


class CustomImageView: UIImageView {

    let imageCache = NSCache<NSString, AnyObject>()

    var imageURLString: String?

    func downloadImageFrom(url: URL) {
        
        if let cachedImage = imageCache.object(forKey: url.absoluteString as NSString) as? UIImage {
            self.image = cachedImage
        } else {
            URLSession.shared.dataTask(with: url) { data, response, error in
                guard let data = data, error == nil else { return }
                DispatchQueue.main.async {
                    let imageToCache = UIImage(data: data)
                    self.imageCache.setObject(imageToCache!, forKey: url.absoluteString as NSString)
                    self.image = imageToCache
                }
            }.resume()
        }
    }
}
