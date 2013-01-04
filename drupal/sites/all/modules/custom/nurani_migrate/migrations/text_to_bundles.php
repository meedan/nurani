<?php

$data = explode("\n",
//discussion_nid,delta,nid,OSIS Work,Osis ID
"97,0,67,,Deut.4.5-8
97,1,69,,1Chr.1.17-29
97,2,71,,quran.2.8-18
99,0,73,nrsv_en,Gen.1.1-4
99,1,75,nrsv_en,John.1.1-9
99,2,77,,quran.24.35
101,0,79,,Gen.18.1-16
101,1,81,,Heb.11.3-13
101,2,83,,quran.15.51-56
103,0,85,,quran.31.12-19
105,0,87,,Ps.123.1-4
105,1,89,,Rev.22.1-7;Rev.22.16-20
105,2,91,,quran.12.11-13;quran.12.80-87
107,0,93,,Job.38.1-8
107,1,95,,Rom.1.16-32
227,0,211,,Deut.6.4-9
227,1,217,,Eph.4.11-16
227,2,221,,quran.4.59
1038,0,1036,nrsv_en,Luke.8.40-56
1054,0,1048,nrsv_en,Mark.11.27-33
1054,1,1065,quran_ahmedali_en,quran.2.247-249
1054,2,1079,,Josh.1.10-18
1095,0,1093,nrsv_en,Acts.19.23-29
1095,1,1091,quran_ahmedali_en,quran.58.7-10
1095,2,1089,jps_2000_en,Num.16.1-6
1253,0,1251,jps_1985_en,Gen.1.1-5
1365,0,1123,nrsv_en,John.1.1-5
1365,2,1425,quran_sahih_en,quran.41.9-12
1681,0,1675,jps_1985_en,Exod.3.1-8
1681,1,1765,quran_ahmedali_en,quran.20.9-23
1681,2,1827,nrsv_en,Acts.9.1-9");

$map = array();
foreach ($data as $datum) {
	list($discussion_nid, $delta, $nid, $osisIDWork,$osisID) = explode(',', $datum);

	$map[$nid] = array(
		'osisIDWork' => $osisIDWork,
		'osisID' => $osisID,
	);
}

var_export($map);
