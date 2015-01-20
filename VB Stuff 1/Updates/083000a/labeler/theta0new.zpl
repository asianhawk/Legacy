~JSB            ^FX JS=Backup seq ON, A=After print, B=Before print
^PRA,A          ^FX PR=Print speed, A=2 IPS Pront SPD, A=2 IPS Slew SPD
^XA                 ^FX XA=Formatting start
^FX  ~TA-20          ^FX TA=Tear off distance, -120 to 120
^MFL,L    ^FX MFL,L=Media feed at power on, L=One or more lbls
^MMP            ^FX MM=Print mode, P=Peel off, C= Cutter Mode (pg3-3)
^MNY            ^FX MN=Media tracking, Y=Non-continuous
^MTT            ^FX MT=Media type, T=Thermal transfer
^MD30           ^FX MD=Media darkness, -30 to 30 range
^LH100,20       ^FX LH=Label home, X axis, Y axis
^LT35           ^FX LT=Label top, -64 to 64 range
^FWN            ^FX FW=Field orientation, I=inverted 180
^FO210,0^AD^FD\CONCODE\^FS^FX
^FO50,20^BY2,1,30^B3,N,40,Y,N^FD\d:^FS ^FX 78A=Human field, B=Font id  FD=Field data
^PQ1            ^FX BY=Barcode element module chg  B3=code 39, PQ=print quantity
^XZ             ^FX XZ=end of format






