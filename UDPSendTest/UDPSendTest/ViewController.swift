//
//  ViewController.swift
//  UDPSendTest
//
//  Created by KenUchida on 2019/02/09.
//  Copyright © 2019 KenUchida. All rights reserved.
//

import UIKit
import CoreMotion

class ViewController: UIViewController {

    @IBOutlet weak var ip: UITextField!
    @IBOutlet weak var portString: UITextField!

    // MotionManager
    let motionManager = CMMotionManager()
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    
        ip.text = "127.0.0.1";
        portString.text = "8000";
        
        if motionManager.isAccelerometerAvailable{
            // intervalの設定 [sec]
            motionManager.accelerometerUpdateInterval = 0.02
            
            // センサー値の取得開始
            motionManager.startAccelerometerUpdates(
                to: OperationQueue.current!,
                withHandler: {(accelData: CMAccelerometerData?, errorOC: Error?) in
                    self.outputAccelData(acceleration: accelData!.acceleration)
            })
            
        }

    }
    
    @IBOutlet weak var labelAcceleration: UILabel!
    //
    func outputAccelData(acceleration: CMAcceleration){
        ut_test(acceleration.x,
                acceleration.y,
                acceleration.z);
        
        labelAcceleration.text = String(format: "x = %f\ny = %f\nz = %f",
                                        acceleration.x,
                                        acceleration.y,
                                        acceleration.z)

    }
    
    @IBAction func OnSend(_ sender: Any) {

        let _ip = ip.text?.cString(using: .utf8)
        let _port = Int32(8000)
        
        ut_open(_ip,_port);

//        ut_test();
//        ut_close();
    }

    /*
     
     
     */
    
    
}

