"""
This is a simple program to process the raw measured data.

The error sample of the torque measurement is removed and a low pass filter is used for the motor current.

The processed data is saved in the folder of "data_filtered"

"""
__date__ ="$Oct 21, 2016 12:40:59 AM$"
import numpy as np
import pylab as p
from scipy.signal import butter, lfilter, freqz

## low pass filter 
def butter_lowpass(cutoff, fs, order=5):
    nyq = 0.5 * fs
    normal_cutoff = cutoff / nyq
    b, a = butter(order, normal_cutoff, btype='low', analog=False)
    return b, a

def butter_lowpass_filter(data, cutoff, fs, order=5):
    b, a = butter_lowpass(cutoff, fs, order=order)
    y = lfilter(b, a, data)
    return y
order = 6
fs = 50     # sample rate, Hz
cutoff = 5  # desired cutoff frequency of the filter, Hz
p.rcParams.update({'font.size': 16})
for exp_idx in range(1):
	data_filtered=[]
	filename = "./Inclination_34.8/in35_pos4_v5%d_25102016.csv"%exp_idx
	dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
	for i in range(5,len(dat["time"])):
		print "exp idx", exp_idx,"data",i
		I_lpf = butter_lowpass_filter(dat["tau_current"], cutoff, fs, order)    # a low pass filter is used for the motor current
		if abs(dat["tau_sensor"][i]-dat["tau_sensor"][i-5:i+5].mean())<1 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
		    ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_current"][i],I_lpf[i],dat["q_spring_meas"][i], dat["dq_meas"][i]]
		    data_filtered.append(np.array(ob_vec))

	data_f=np.array(data_filtered)
	print "data_f 1",data_f.shape
	data_size=len(data_f[:,0])
	data_f=data_f[np.linspace(0, data_size-1, num=3000, dtype=int),:]
	print "data_f",data_f.shape
	np.savetxt("./data_filtered_inclination_34.8/4by3_springmodeling_25102016_filtered_in0_pos4_v5%d.csv"%exp_idx,data_f,delimiter= ",")
	p.figure()
	p.subplot(2,2,1)
	p.plot(data_f[:,0], data_f[:,2]) ## measured current 
	p.plot(data_f[:,0], data_f[:,3]) ## current after low pass filter
	p.grid()
	p.legend(["motor current_I*x","motor current_filtered"])
	p.ylabel("Current [A]", fontsize=20)
	p.xlabel("Time[s]", fontsize=20)

	p.subplot(2,2,2)
	p.plot(data_f[:,0], data_f[:,4]*180/np.pi) ## measured deflection
	p.grid()
	p.legend(["deflection"])
	p.ylabel("Def [deg]", fontsize=20)
	p.xlabel("Time[s]", fontsize=20)

	p.subplot(2,2,3)
	p.plot(data_f[:,0], data_f[:,5]*180/np.pi) ## measured velocity
	p.grid()
	p.legend(["velocity"])
	p.ylabel("Vel [deg/s]", fontsize=20)
	p.xlabel("Time[s]", fontsize=20)

	p.subplot(2,2,4)
	p.plot(data_f[:,0], data_f[:,1],'b+') ## measured velocity
	p.grid()
	p.legend(["tau_meas (sensor)"])
	p.ylim([-20,20])
	p.ylabel("Torque [Nm]", fontsize=20)
	p.xlabel("Time[s]", fontsize=20)

	#p.suptitle("4by3_springmodeling_15092016_Exp%d"%exp_idx)
	p.savefig("./img/4by3_springmodeling_25102016_filtered_in34.8_pos4%d_v50.png"%exp_idx)
	#p.show()
	p.close("all")		

