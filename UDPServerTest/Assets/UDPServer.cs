using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//  UDP
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

public class UDPServer : MonoBehaviour
{
    [SerializeField] int LOCA_LPORT = 8000;

    static UDPServer udpserver;
    static UdpClient udp;
    Thread thread;
    Vector3 rotate = new Vector3();

    void Start()
    {
        udpserver = this;
        udp = new UdpClient(LOCA_LPORT);
        udp.Client.ReceiveTimeout = 1000;
        thread = new Thread(new ThreadStart(ThreadMethod));
        thread.Start();
    }

    void Update()
    {

    }


    public float speed = 3f;

    private void FixedUpdate()
    {
        var angle = this.gameObject.transform.eulerAngles;
        angle.y += rotate.y * 10f;
        this.gameObject.transform.eulerAngles = angle;

        //        this.gameObject.transform.position += Vector3.forward * speed * Time.deltaTime;

        var r = GetComponent<Rigidbody>();
        r.velocity +=
        this.gameObject.transform.rotation * Vector3.forward * speed * Time.deltaTime;  
    }

    void OnApplicationQuit()
    {
        thread.Abort();
    }

    private static void ThreadMethod()
    {
        while (true)
        {
            try
            {
                IPEndPoint remoteEP = null;
                var data = udp.Receive(ref remoteEP);

                Debug.Log(data.Length.ToString());


                double[] v =  new double [3];
#if true
                unsafe
                {
                    fixed (byte* p = data)
                    {
                        v[0] = *(double*)p ;
                        v[1] = *(double*)&p[8] ;
                        v[2] = *(double*)&p[16];
                    }
                }
#endif
//                Debug.Log(v[0].ToString()+"/" + v[1].ToString()+"/" + v[2].ToString() );
                udpserver.rotate = new Vector3(
                    (float)v[0],
                    (float)v[1],
                    (float)v[2]);

            }
            catch
            {

            }
        }
    }
}




