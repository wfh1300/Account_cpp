#include "EXCHANGE_CODE.h"
#include <iostream>
#include <hikyuu/Log.h>
namespace rt {

	EXCHANGE_CODE::EXCHANGE_CODE() {

		m_table["sn1901"] = "SHFE";
		m_table["sn1902"] = "SHFE";
		m_table["sn1903"] = "SHFE";
		m_table["sn1904"] = "SHFE";
		m_table["sn1905"] = "SHFE";
		m_table["sn1906"] = "SHFE";
		m_table["sn1907"] = "SHFE";
		m_table["sn1908"] = "SHFE";
		m_table["sn1909"] = "SHFE";
		m_table["sn1910"] = "SHFE";
		m_table["sn1911"] = "SHFE";
		m_table["snl8"] = "SHFE";
		m_table["snl9"] = "SHFE";
		m_table["sp1906"] = "SHFE";
		m_table["sp1907"] = "SHFE";
		m_table["sp1908"] = "SHFE";
		m_table["sp1909"] = "SHFE";
		m_table["sp1910"] = "SHFE";
		m_table["sp1911"] = "SHFE";
		m_table["spl8"] = "SHFE";
		m_table["spl9"] = "SHFE";
		m_table["wr1903"] = "SHFE";
		m_table["wr1904"] = "SHFE";
		m_table["wr1905"] = "SHFE";
		m_table["wr1906"] = "SHFE";
		m_table["wr1907"] = "SHFE";
		m_table["wr1908"] = "SHFE";
		m_table["wr1909"] = "SHFE";
		m_table["wr1910"] = "SHFE";
		m_table["wr1911"] = "SHFE";
		m_table["wrl8"] = "SHFE";
		m_table["wrl9"] = "SHFE";
		m_table["zn1812"] = "SHFE";
		m_table["zn1901"] = "SHFE";
		m_table["zn1902"] = "SHFE";
		m_table["zn1903"] = "SHFE";
		m_table["zn1904"] = "SHFE";
		m_table["zn1905"] = "SHFE";
		m_table["zn1906"] = "SHFE";
		m_table["zn1907"] = "SHFE";
		m_table["zn1908"] = "SHFE";
		m_table["zn1909"] = "SHFE";
		m_table["zn1910"] = "SHFE";
		m_table["zn1911"] = "SHFE";
		m_table["znl8"] = "SHFE";
		m_table["znl9"] = "SHFE";
		m_table["ma1902"] = "ZCE";
		m_table["ma1903"] = "ZCE";
		m_table["ma1904"] = "ZCE";
		m_table["ma1905"] = "ZCE";
		m_table["ma1906"] = "ZCE";
		m_table["ma1907"] = "ZCE";
		m_table["ma1908"] = "ZCE";
		m_table["ma1909"] = "ZCE";
		m_table["ma1910"] = "ZCE";
		m_table["ma1911"] = "ZCE";
		m_table["mal8"] = "ZCE";
		m_table["mal9"] = "ZCE";
		m_table["oi1901"] = "ZCE";
		m_table["oi1903"] = "ZCE";
		m_table["oi1905"] = "ZCE";
		m_table["oi1907"] = "ZCE";
		m_table["oi1909"] = "ZCE";
		m_table["oi1911"] = "ZCE";
		m_table["oil8"] = "ZCE";
		m_table["oil9"] = "ZCE";
		m_table["pm1901"] = "ZCE";
		m_table["pm1903"] = "ZCE";
		m_table["pm1905"] = "ZCE";
		m_table["pm1907"] = "ZCE";
		m_table["pm1909"] = "ZCE";
		m_table["pm1911"] = "ZCE";
		m_table["pml8"] = "ZCE";
		m_table["pml9"] = "ZCE";
		m_table["ri1901"] = "ZCE";
		m_table["ri1903"] = "ZCE";
		m_table["ri1905"] = "ZCE";
		m_table["ri1907"] = "ZCE";
		m_table["ri1909"] = "ZCE";
		m_table["ri1911"] = "ZCE";
		m_table["rm1901"] = "ZCE";
		m_table["rm1903"] = "ZCE";
		m_table["rm1905"] = "ZCE";
		m_table["rm1907"] = "ZCE";
		m_table["rm1908"] = "ZCE";
		m_table["rm1909"] = "ZCE";
		m_table["rm1911"] = "ZCE";
		m_table["rml8"] = "ZCE";
		m_table["rml9"] = "ZCE";
		m_table["rs1907"] = "ZCE";
		m_table["rs1908"] = "ZCE";
		m_table["rs1909"] = "ZCE";
		m_table["rs1911"] = "ZCE";
		m_table["rsl8"] = "ZCE";
		m_table["rsl9"] = "ZCE";
		m_table["sf1812"] = "ZCE";
		m_table["sf1901"] = "ZCE";
		m_table["sf1902"] = "ZCE";
		m_table["sf1903"] = "ZCE";
		m_table["sf1904"] = "ZCE";
		m_table["sf1905"] = "ZCE";
		m_table["sf1906"] = "ZCE";
		m_table["sf1907"] = "ZCE";
		m_table["sf1908"] = "ZCE";
		m_table["sf1909"] = "ZCE";
		m_table["sf1910"] = "ZCE";
		m_table["sf1911"] = "ZCE";
		m_table["sfl8"] = "ZCE";
		m_table["sfl9"] = "ZCE";
		m_table["sm1812"] = "ZCE";
		m_table["sm1901"] = "ZCE";
		m_table["sm1902"] = "ZCE";
		m_table["sm1903"] = "ZCE";
		m_table["sm1904"] = "ZCE";
		m_table["sm1905"] = "ZCE";
		m_table["sm1906"] = "ZCE";
		m_table["sm1907"] = "ZCE";
		m_table["sm1908"] = "ZCE";
		m_table["sm1909"] = "ZCE";
		m_table["sm1910"] = "ZCE";
		m_table["sm1911"] = "ZCE";
		m_table["sml8"] = "ZCE";
		m_table["sml9"] = "ZCE";
		m_table["sr1901"] = "ZCE";
		m_table["sr1903"] = "ZCE";
		m_table["sr1905"] = "ZCE";
		m_table["sr1907"] = "ZCE";
		m_table["sr1909"] = "ZCE";
		m_table["sr1911"] = "ZCE";
		m_table["srl8"] = "ZCE";
		m_table["srl9"] = "ZCE";
		m_table["ta1812"] = "ZCE";
		m_table["ta1901"] = "ZCE";
		m_table["ta1902"] = "ZCE";
		m_table["ta1903"] = "ZCE";
		m_table["ta1904"] = "ZCE";
		m_table["ta1905"] = "ZCE";
		m_table["ta1906"] = "ZCE";
		m_table["ta1907"] = "ZCE";
		m_table["ta1908"] = "ZCE";
		m_table["ta1909"] = "ZCE";
		m_table["ta1910"] = "ZCE";
		m_table["ta1911"] = "ZCE";
		m_table["tal8"] = "ZCE";
		m_table["tal9"] = "ZCE";
		m_table["wh1901"] = "ZCE";
		m_table["wh1903"] = "ZCE";
		m_table["wh1905"] = "ZCE";
		m_table["wh1907"] = "ZCE";
		m_table["wh1909"] = "ZCE";
		m_table["wh1911"] = "ZCE";
		m_table["whl8"] = "ZCE";
		m_table["whl9"] = "ZCE";
		m_table["zc1812"] = "ZCE";
		m_table["zc1901"] = "ZCE";
		m_table["zc1902"] = "ZCE";
		m_table["zc1903"] = "ZCE";
		m_table["zc1904"] = "ZCE";
		m_table["zc1905"] = "ZCE";
		m_table["zc1906"] = "ZCE";
		m_table["zc1907"] = "ZCE";
		m_table["zc1908"] = "ZCE";
		m_table["zc1909"] = "ZCE";
		m_table["zc1910"] = "ZCE";
		m_table["zc1911"] = "ZCE";
		m_table["zc1912"] = "ZCE";
		m_table["zcl8"] = "ZCE";
		m_table["zcl9"] = "ZCE";
		m_table["a1901"] = "DCE";
		m_table["a1903"] = "DCE";
		m_table["a1905"] = "DCE";
		m_table["a1907"] = "DCE";
		m_table["a1909"] = "DCE";
		m_table["a1911"] = "DCE";
		m_table["a2001"] = "DCE";
		m_table["al8"] = "DCE";
		m_table["al9"] = "DCE";
		m_table["b1812"] = "DCE";
		m_table["b1901"] = "DCE";
		m_table["b1902"] = "DCE";
		m_table["b1903"] = "DCE";
		m_table["b1904"] = "DCE";
		m_table["b1905"] = "DCE";
		m_table["b1906"] = "DCE";
		m_table["b1907"] = "DCE";
		m_table["b1908"] = "DCE";
		m_table["b1909"] = "DCE";
		m_table["b1910"] = "DCE";
		m_table["b1911"] = "DCE";
		m_table["bb1812"] = "DCE";
		m_table["bb1901"] = "DCE";
		m_table["bb1902"] = "DCE";
		m_table["bb1903"] = "DCE";
		m_table["bb1904"] = "DCE";
		m_table["bb1905"] = "DCE";
		m_table["bb1906"] = "DCE";
		m_table["bb1907"] = "DCE";
		m_table["bb1908"] = "DCE";
		m_table["bb1909"] = "DCE";
		m_table["bb1910"] = "DCE";
		m_table["bb1911"] = "DCE";
		m_table["bbl8"] = "DCE";
		m_table["bbl9"] = "DCE";
		m_table["bl8"] = "DCE";
		m_table["bl9"] = "DCE";
		m_table["c1901"] = "DCE";
		m_table["c1903"] = "DCE";
		m_table["c1905"] = "DCE";
		m_table["c1907"] = "DCE";
		m_table["c1909"] = "DCE";
		m_table["c1911"] = "DCE";
		m_table["cl8"] = "DCE";
		m_table["cl9"] = "DCE";
		m_table["cs1901"] = "DCE";
		m_table["cs1903"] = "DCE";
		m_table["cs1905"] = "DCE";
		m_table["cs1907"] = "DCE";
		m_table["cs1909"] = "DCE";
		m_table["cs1911"] = "DCE";
		m_table["csl8"] = "DCE";
		m_table["csl9"] = "DCE";
		m_table["eg1906"] = "DCE";
		m_table["eg1907"] = "DCE";
		m_table["eg1908"] = "DCE";
		m_table["eg1909"] = "DCE";
		m_table["eg1910"] = "DCE";
		m_table["eg1911"] = "DCE";
		m_table["egl8"] = "DCE";
		m_table["egl9"] = "DCE";
		m_table["fb1812"] = "DCE";
		m_table["fb1901"] = "DCE";
		m_table["fb1902"] = "DCE";
		m_table["fb1903"] = "DCE";
		m_table["fb1904"] = "DCE";
		m_table["fb1905"] = "DCE";
		m_table["fb1906"] = "DCE";
		m_table["fb1907"] = "DCE";
		m_table["fb1908"] = "DCE";
		m_table["fb1909"] = "DCE";
		m_table["fb1910"] = "DCE";
		m_table["fb1911"] = "DCE";
		m_table["fbl8"] = "DCE";
		m_table["fbl9"] = "DCE";
		m_table["i1812"] = "DCE";
		m_table["i1901"] = "DCE";
		m_table["i1902"] = "DCE";
		m_table["i1903"] = "DCE";
		m_table["i1904"] = "DCE";
		m_table["i1905"] = "DCE";
		m_table["i1906"] = "DCE";
		m_table["i1907"] = "DCE";
		m_table["i1908"] = "DCE";
		m_table["i1909"] = "DCE";
		m_table["i1910"] = "DCE";
		m_table["i1911"] = "DCE";
		m_table["il8"] = "DCE";
		m_table["il9"] = "DCE";
		m_table["j1812"] = "DCE";
		m_table["j1901"] = "DCE";
		m_table["j1902"] = "DCE";
		m_table["j1903"] = "DCE";
		m_table["j1904"] = "DCE";
		m_table["j1905"] = "DCE";
		m_table["j1906"] = "DCE";
		m_table["j1907"] = "DCE";
		m_table["j1908"] = "DCE";
		m_table["j1909"] = "DCE";
		m_table["j1910"] = "DCE";
		m_table["j1911"] = "DCE";
		m_table["jd1812"] = "DCE";
		m_table["jd1901"] = "DCE";
		m_table["jd1902"] = "DCE";
		m_table["jd1903"] = "DCE";
		m_table["jd1904"] = "DCE";
		m_table["jd1905"] = "DCE";
		m_table["jd1906"] = "DCE";
		m_table["jd1907"] = "DCE";
		m_table["jd1908"] = "DCE";
		m_table["jd1909"] = "DCE";
		m_table["jd1910"] = "DCE";
		m_table["jd1911"] = "DCE";
		m_table["jdl8"] = "DCE";
		m_table["jdl9"] = "DCE";
		m_table["jl8"] = "DCE";
		m_table["jl9"] = "DCE";
		m_table["jm1812"] = "DCE";
		m_table["jm1901"] = "DCE";
		m_table["jm1902"] = "DCE";
		m_table["jm1903"] = "DCE";
		m_table["jm1904"] = "DCE";
		m_table["jm1905"] = "DCE";
		m_table["jm1906"] = "DCE";
		m_table["jm1907"] = "DCE";
		m_table["jm1908"] = "DCE";
		m_table["jm1909"] = "DCE";
		m_table["jm1910"] = "DCE";
		m_table["jm1911"] = "DCE";
		m_table["jml8"] = "DCE";
		m_table["jml9"] = "DCE";
		m_table["l1812"] = "DCE";
		m_table["l1901"] = "DCE";
		m_table["l1902"] = "DCE";
		m_table["l1903"] = "DCE";
		m_table["l1904"] = "DCE";
		m_table["l1905"] = "DCE";
		m_table["l1906"] = "DCE";
		m_table["l1907"] = "DCE";
		m_table["l1908"] = "DCE";
		m_table["l1909"] = "DCE";
		m_table["l1910"] = "DCE";
		m_table["l1911"] = "DCE";
		m_table["ll8"] = "DCE";
		m_table["ll9"] = "DCE";
		m_table["m1812"] = "DCE";
		m_table["m1901"] = "DCE";
		m_table["m1903"] = "DCE";
		m_table["m1905"] = "DCE";
		m_table["m1907"] = "DCE";
		m_table["m1908"] = "DCE";
		m_table["m1909"] = "DCE";
		m_table["m1911"] = "DCE";
		m_table["ml8"] = "DCE";
		m_table["ml9"] = "DCE";
		m_table["p1812"] = "DCE";
		m_table["p1901"] = "DCE";
		m_table["p1902"] = "DCE";
		m_table["p1903"] = "DCE";
		m_table["p1904"] = "DCE";
		m_table["p1905"] = "DCE";
		m_table["p1906"] = "DCE";
		m_table["p1907"] = "DCE";
		m_table["p1908"] = "DCE";
		m_table["p1909"] = "DCE";
		m_table["p1910"] = "DCE";
		m_table["p1911"] = "DCE";
		m_table["pl8"] = "DCE";
		m_table["pl9"] = "DCE";
		m_table["pp1812"] = "DCE";
		m_table["pp1901"] = "DCE";
		m_table["pp1902"] = "DCE";
		m_table["pp1903"] = "DCE";
		m_table["pp1904"] = "DCE";
		m_table["pp1905"] = "DCE";
		m_table["pp1906"] = "DCE";
		m_table["pp1907"] = "DCE";
		m_table["pp1908"] = "DCE";
		m_table["pp1909"] = "DCE";
		m_table["pp1910"] = "DCE";
		m_table["pp1911"] = "DCE";
		m_table["ppl8"] = "DCE";
		m_table["ppl9"] = "DCE";
		m_table["v1812"] = "DCE";
		m_table["v1901"] = "DCE";
		m_table["v1902"] = "DCE";
		m_table["v1903"] = "DCE";
		m_table["v1904"] = "DCE";
		m_table["v1905"] = "DCE";
		m_table["v1906"] = "DCE";
		m_table["v1907"] = "DCE";
		m_table["v1908"] = "DCE";
		m_table["v1909"] = "DCE";
		m_table["v1910"] = "DCE";
		m_table["v1911"] = "DCE";
		m_table["vl8"] = "DCE";
		m_table["vl9"] = "DCE";
		m_table["y1812"] = "DCE";
		m_table["y1901"] = "DCE";
		m_table["y1903"] = "DCE";
		m_table["y1905"] = "DCE";
		m_table["y1907"] = "DCE";
		m_table["y1908"] = "DCE";
		m_table["y1909"] = "DCE";
		m_table["y1911"] = "DCE";
		m_table["yl8"] = "DCE";
		m_table["yl9"] = "DCE";
		m_table["ag1812"] = "SHFE";
		m_table["ag1901"] = "SHFE";
		m_table["ag1902"] = "SHFE";
		m_table["ag1903"] = "SHFE";
		m_table["ag1904"] = "SHFE";
		m_table["ag1905"] = "SHFE";
		m_table["ag1906"] = "SHFE";
		m_table["ag1907"] = "SHFE";
		m_table["ag1908"] = "SHFE";
		m_table["ag1909"] = "SHFE";
		m_table["ag1910"] = "SHFE";
		m_table["ag1911"] = "SHFE";
		m_table["agl8"] = "SHFE";
		m_table["agl9"] = "SHFE";
		m_table["al1812"] = "SHFE";
		m_table["al1901"] = "SHFE";
		m_table["al1902"] = "SHFE";
		m_table["al1903"] = "SHFE";
		m_table["al1904"] = "SHFE";
		m_table["al1905"] = "SHFE";
		m_table["al1906"] = "SHFE";
		m_table["al1907"] = "SHFE";
		m_table["al1908"] = "SHFE";
		m_table["al1909"] = "SHFE";
		m_table["al1910"] = "SHFE";
		m_table["al1911"] = "SHFE";
		m_table["all8"] = "SHFE";
		m_table["all9"] = "SHFE";
		m_table["au1812"] = "SHFE";
		m_table["au1901"] = "SHFE";
		m_table["au1902"] = "SHFE";
		m_table["au1904"] = "SHFE";
		m_table["au1906"] = "SHFE";
		m_table["au1908"] = "SHFE";
		m_table["au1910"] = "SHFE";
		m_table["au1912"] = "SHFE";
		m_table["aul8"] = "SHFE";
		m_table["aul9"] = "SHFE";
		m_table["bu1812"] = "SHFE";
		m_table["bu1901"] = "SHFE";
		m_table["bu1902"] = "SHFE";
		m_table["bu1903"] = "SHFE";
		m_table["bu1904"] = "SHFE";
		m_table["bu1905"] = "SHFE";
		m_table["bu1906"] = "SHFE";
		m_table["bu1909"] = "SHFE";
		m_table["bu1912"] = "SHFE";
		m_table["bu2003"] = "SHFE";
		m_table["bu2006"] = "SHFE";
		m_table["bu2009"] = "SHFE";
		m_table["bul8"] = "SHFE";
		m_table["bul9"] = "SHFE";
		m_table["cu1812"] = "SHFE";
		m_table["cu1901"] = "SHFE";
		m_table["cu1902"] = "SHFE";
		m_table["cu1903"] = "SHFE";
		m_table["cu1904"] = "SHFE";
		m_table["cu1905"] = "SHFE";
		m_table["cu1906"] = "SHFE";
		m_table["cu1907"] = "SHFE";
		m_table["cu1908"] = "SHFE";
		m_table["cu1909"] = "SHFE";
		m_table["cu1910"] = "SHFE";
		m_table["cu1911"] = "SHFE";
		m_table["cul8"] = "SHFE";
		m_table["cul9"] = "SHFE";
		m_table["fu1901"] = "SHFE";
		m_table["fu1902"] = "SHFE";
		m_table["fu1903"] = "SHFE";
		m_table["fu1904"] = "SHFE";
		m_table["fu1905"] = "SHFE";
		m_table["fu1906"] = "SHFE";
		m_table["fu1907"] = "SHFE";
		m_table["fu1908"] = "SHFE";
		m_table["fu1909"] = "SHFE";
		m_table["fu1910"] = "SHFE";
		m_table["fu1911"] = "SHFE";
		m_table["fu1912"] = "SHFE";
		m_table["ful8"] = "SHFE";
		m_table["ful9"] = "SHFE";
		m_table["hc1812"] = "SHFE";
		m_table["hc1901"] = "SHFE";
		m_table["hc1902"] = "SHFE";
		m_table["hc1903"] = "SHFE";
		m_table["hc1904"] = "SHFE";
		m_table["hc1905"] = "SHFE";
		m_table["hc1906"] = "SHFE";
		m_table["hc1907"] = "SHFE";
		m_table["hc1908"] = "SHFE";
		m_table["hc1909"] = "SHFE";
		m_table["hc1910"] = "SHFE";
		m_table["hc1911"] = "SHFE";
		m_table["hcl8"] = "SHFE";
		m_table["hcl9"] = "SHFE";
		m_table["ni1812"] = "SHFE";
		m_table["ni1901"] = "SHFE";
		m_table["ni1902"] = "SHFE";
		m_table["ni1903"] = "SHFE";
		m_table["ni1904"] = "SHFE";
		m_table["ni1905"] = "SHFE";
		m_table["ni1906"] = "SHFE";
		m_table["ni1907"] = "SHFE";
		m_table["ni1908"] = "SHFE";
		m_table["ni1909"] = "SHFE";
		m_table["ni1910"] = "SHFE";
		m_table["ni1911"] = "SHFE";
		m_table["nil8"] = "SHFE";
		m_table["nil9"] = "SHFE";
		m_table["pb1812"] = "SHFE";
		m_table["pb1901"] = "SHFE";
		m_table["pb1902"] = "SHFE";
		m_table["pb1903"] = "SHFE";
		m_table["pb1904"] = "SHFE";
		m_table["pb1905"] = "SHFE";
		m_table["pb1906"] = "SHFE";
		m_table["pb1907"] = "SHFE";
		m_table["pb1908"] = "SHFE";
		m_table["pb1909"] = "SHFE";
		m_table["pb1910"] = "SHFE";
		m_table["pb1911"] = "SHFE";
		m_table["pbl8"] = "SHFE";
		m_table["pbl9"] = "SHFE";
		m_table["rb1812"] = "SHFE";
		m_table["rb1901"] = "SHFE";
		m_table["rb1902"] = "SHFE";
		m_table["rb1903"] = "SHFE";
		m_table["rb1904"] = "SHFE";
		m_table["rb1905"] = "SHFE";
		m_table["rb1906"] = "SHFE";
		m_table["rb1907"] = "SHFE";
		m_table["rb1908"] = "SHFE";
		m_table["rb1909"] = "SHFE";
		m_table["rb1910"] = "SHFE";
		m_table["rb1911"] = "SHFE";
		m_table["rbl8"] = "SHFE";
		m_table["rbl9"] = "SHFE";
		m_table["ru1901"] = "SHFE";
		m_table["ru1903"] = "SHFE";
		m_table["ru1904"] = "SHFE";
		m_table["ru1905"] = "SHFE";
		m_table["ru1906"] = "SHFE";
		m_table["ru1907"] = "SHFE";
		m_table["ru1908"] = "SHFE";
		m_table["ru1909"] = "SHFE";
		m_table["ru1910"] = "SHFE";
		m_table["ru1911"] = "SHFE";
		m_table["rul8"] = "SHFE";
		m_table["rul9"] = "SHFE";
		m_table["sc1901"] = "SHFE";
		m_table["sc1902"] = "SHFE";
		m_table["sc1903"] = "SHFE";
		m_table["sc1904"] = "SHFE";
		m_table["sc1905"] = "SHFE";
		m_table["sc1906"] = "SHFE";
		m_table["sc1907"] = "SHFE";
		m_table["sc1908"] = "SHFE";
		m_table["sc1909"] = "SHFE";
		m_table["sc1910"] = "SHFE";
		m_table["sc1911"] = "SHFE";
		m_table["sc1912"] = "SHFE";
		m_table["sc2003"] = "SHFE";
		m_table["sc2006"] = "SHFE";
		m_table["sc2009"] = "SHFE";
		m_table["sc2012"] = "SHFE";
		m_table["sc2103"] = "SHFE";
		m_table["sc2106"] = "SHFE";
		m_table["sc2109"] = "SHFE";
		m_table["sc2112"] = "SHFE";
		m_table["scl8"] = "SHFE";
		m_table["scl9"] = "SHFE";
		m_table["sn1812"] = "SHFE";
		m_table["ap1812"] = "ZCE";
		m_table["ap1901"] = "ZCE";
		m_table["ap1903"] = "ZCE";
		m_table["ap1905"] = "ZCE";
		m_table["ap1907"] = "ZCE";
		m_table["ap1910"] = "ZCE";
		m_table["ap1911"] = "ZCE";
		m_table["apl8"] = "ZCE";
		m_table["apl9"] = "ZCE";
		m_table["cf1901"] = "ZCE";
		m_table["cf1903"] = "ZCE";
		m_table["cf1905"] = "ZCE";
		m_table["cf1907"] = "ZCE";
		m_table["cf1909"] = "ZCE";
		m_table["cf1911"] = "ZCE";
		m_table["cfl8"] = "ZCE";
		m_table["cfl9"] = "ZCE";
		m_table["cy1812"] = "ZCE";
		m_table["cy1901"] = "ZCE";
		m_table["cy1902"] = "ZCE";
		m_table["cy1903"] = "ZCE";
		m_table["cy1904"] = "ZCE";
		m_table["cy1905"] = "ZCE";
		m_table["cy1906"] = "ZCE";
		m_table["cy1907"] = "ZCE";
		m_table["cy1908"] = "ZCE";
		m_table["cy1909"] = "ZCE";
		m_table["cy1910"] = "ZCE";
		m_table["cy1911"] = "ZCE";
		m_table["cyl8"] = "ZCE";
		m_table["cyl9"] = "ZCE";
		m_table["fg1812"] = "ZCE";
		m_table["fg1901"] = "ZCE";
		m_table["fg1902"] = "ZCE";
		m_table["fg1903"] = "ZCE";
		m_table["fg1904"] = "ZCE";
		m_table["fg1905"] = "ZCE";
		m_table["fg1906"] = "ZCE";
		m_table["fg1907"] = "ZCE";
		m_table["fg1908"] = "ZCE";
		m_table["fg1909"] = "ZCE";
		m_table["fg1910"] = "ZCE";
		m_table["fg1911"] = "ZCE";
		m_table["fgl8"] = "ZCE";
		m_table["fgl9"] = "ZCE";
		m_table["jr1901"] = "ZCE";
		m_table["jr1903"] = "ZCE";
		m_table["jr1905"] = "ZCE";
		m_table["jr1907"] = "ZCE";
		m_table["jr1909"] = "ZCE";
		m_table["jr1911"] = "ZCE";
		m_table["jrl8"] = "ZCE";
		m_table["jrl9"] = "ZCE";
		m_table["lr1901"] = "ZCE";
		m_table["lr1903"] = "ZCE";
		m_table["lr1905"] = "ZCE";
		m_table["lr1907"] = "ZCE";
		m_table["lr1909"] = "ZCE";
		m_table["lr1911"] = "ZCE";
		m_table["lrl8"] = "ZCE";
		m_table["lrl9"] = "ZCE";
		m_table["ma1812"] = "ZCE";
		m_table["ma1901"] = "ZCE";
		m_table["ic1812"] = "CFFEX";
		m_table["ic1901"] = "CFFEX";
		m_table["ic1903"] = "CFFEX";
		m_table["ic1906"] = "CFFEX";
		m_table["ic500"] = "CFFEX";
		m_table["icl8"] = "CFFEX";
		m_table["icl9"] = "CFFEX";
		m_table["if1812"] = "CFFEX";
		m_table["if1901"] = "CFFEX";
		m_table["if1903"] = "CFFEX";
		m_table["if1906"] = "CFFEX";
		m_table["ifshfe0"] = "CFFEX";
		m_table["ifl0"] = "CFFEX";
		m_table["ifl1"] = "CFFEX";
		m_table["ifl2"] = "CFFEX";
		m_table["ifl3"] = "CFFEX";
		m_table["ifl8"] = "CFFEX";
		m_table["ifl9"] = "CFFEX";
		m_table["ih1812"] = "CFFEX";
		m_table["ih1901"] = "CFFEX";
		m_table["ih1903"] = "CFFEX";
		m_table["ih1906"] = "CFFEX";
		m_table["ih50"] = "CFFEX";
		m_table["ihl8"] = "CFFEX";
		m_table["ihl9"] = "CFFEX";
		m_table["t1812"] = "CFFEX";
		m_table["t1903"] = "CFFEX";
		m_table["t1906"] = "CFFEX";
		m_table["tf1812"] = "CFFEX";
		m_table["tf1903"] = "CFFEX";
		m_table["tf1906"] = "CFFEX";
		m_table["tfl0"] = "CFFEX";
		m_table["tfl1"] = "CFFEX";
		m_table["tfl2"] = "CFFEX";
		m_table["tfl8"] = "CFFEX";
		m_table["tfl9"] = "CFFEX";
		m_table["tl8"] = "CFFEX";
		m_table["tl9"] = "CFFEX";
		m_table["ts1812"] = "CFFEX";
		m_table["ts1903"] = "CFFEX";
		m_table["ts1906"] = "CFFEX";
		m_table["tsl8"] = "CFFEX";
		m_table["tsl9"] = "CFFEX";

	}

	string EXCHANGE_CODE::exchange(const string& instrument_code) const {
		if (!m_table.count(instrument_code)) {
			HKU_ERROR("期货合约不存在！");
			return "Unknown";
		}
		return m_table.find(instrument_code)->second;
	}
	
	/*
	map<string, string> EXCHANGE_CODE::m_table{
		{"sn1901","SHFE"},
		{"sn1902","SHFE"},
		{"sn1903","SHFE"},
		{"sn1904","SHFE"},
		{"sn1905","SHFE"},
		{"sn1906","SHFE"},
		{"sn1907","SHFE"},
		{"sn1908","SHFE"},
		{"sn1909","SHFE"},
		{"sn1910","SHFE"},
		{"sn1911","SHFE"},
		{"snl8","SHFE"},
		{"snl9","SHFE"},
		{"sp1906","SHFE"},
		{"sp1907","SHFE"},
		{"sp1908","SHFE"},
		{"sp1909","SHFE"},
		{"sp1910","SHFE"},
		{"sp1911","SHFE"},
		{"spl8","SHFE"},
		{"spl9","SHFE"},
		{"wr1903","SHFE"},
		{"wr1904","SHFE"},
		{"wr1905","SHFE"},
		{"wr1906","SHFE"},
		{"wr1907","SHFE"},
		{"wr1908","SHFE"},
		{"wr1909","SHFE"},
		{"wr1910","SHFE"},
		{"wr1911","SHFE"},
		{"wrl8","SHFE"},
		{"wrl9","SHFE"},
		{"zn1812","SHFE"},
		{"zn1901","SHFE"},
		{"zn1902","SHFE"},
		{"zn1903","SHFE"},
		{"zn1904","SHFE"},
		{"zn1905","SHFE"},
		{"zn1906","SHFE"},
		{"zn1907","SHFE"},
		{"zn1908","SHFE"},
		{"zn1909","SHFE"},
		{"zn1910","SHFE"},
		{"zn1911","SHFE"},
		{"znl8","SHFE"},
		{"znl9","SHFE"},
		{"ma1902","ZCE"},
		{"ma1903","ZCE"},
		{"ma1904","ZCE"},
		{"ma1905","ZCE"},
		{"ma1906","ZCE"},
		{"ma1907","ZCE"},
		{"ma1908","ZCE"},
		{"ma1909","ZCE"},
		{"ma1910","ZCE"},
		{"ma1911","ZCE"},
		{"mal8","ZCE"},
		{"mal9","ZCE"},
		{"oi1901","ZCE"},
		{"oi1903","ZCE"},
		{"oi1905","ZCE"},
		{"oi1907","ZCE"},
		{"oi1909","ZCE"},
		{"oi1911","ZCE"},
		{"oil8","ZCE"},
		{"oil9","ZCE"},
		{"pm1901","ZCE"},
		{"pm1903","ZCE"},
		{"pm1905","ZCE"},
		{"pm1907","ZCE"},
		{"pm1909","ZCE"},
		{"pm1911","ZCE"},
		{"pml8","ZCE"},
		{"pml9","ZCE"},
		{"ri1901","ZCE"},
		{"ri1903","ZCE"},
		{"ri1905","ZCE"},
		{"ri1907","ZCE"},
		{"ri1909","ZCE"},
		{"ri1911","ZCE"},
		{"rm1901","ZCE"},
		{"rm1903","ZCE"},
		{"rm1905","ZCE"},
		{"rm1907","ZCE"},
		{"rm1908","ZCE"},
		{"rm1909","ZCE"},
		{"rm1911","ZCE"},
		{"rml8","ZCE"},
		{"rml9","ZCE"},
		{"rs1907","ZCE"},
		{"rs1908","ZCE"},
		{"rs1909","ZCE"},
		{"rs1911","ZCE"},
		{"rsl8","ZCE"},
		{"rsl9","ZCE"},
		{"sf1812","ZCE"},
		{"sf1901","ZCE"},
		{"sf1902","ZCE"},
		{"sf1903","ZCE"},
		{"sf1904","ZCE"},
		{"sf1905","ZCE"},
		{"sf1906","ZCE"},
		{"sf1907","ZCE"},
		{"sf1908","ZCE"},
		{"sf1909","ZCE"},
		{"sf1910","ZCE"},
		{"sf1911","ZCE"},
		{"sfl8","ZCE"},
		{"sfl9","ZCE"},
		{"sm1812","ZCE"},
		{"sm1901","ZCE"},
		{"sm1902","ZCE"},
		{"sm1903","ZCE"},
		{"sm1904","ZCE"},
		{"sm1905","ZCE"},
		{"sm1906","ZCE"},
		{"sm1907","ZCE"},
		{"sm1908","ZCE"},
		{"sm1909","ZCE"},
		{"sm1910","ZCE"},
		{"sm1911","ZCE"},
		{"sml8","ZCE"},
		{"sml9","ZCE"},
		{"sr1901","ZCE"},
		{"sr1903","ZCE"},
		{"sr1905","ZCE"},
		{"sr1907","ZCE"},
		{"sr1909","ZCE"},
		{"sr1911","ZCE"},
		{"srl8","ZCE"},
		{"srl9","ZCE"},
		{"ta1812","ZCE"},
		{"ta1901","ZCE"},
		{"ta1902","ZCE"},
		{"ta1903","ZCE"},
		{"ta1904","ZCE"},
		{"ta1905","ZCE"},
		{"ta1906","ZCE"},
		{"ta1907","ZCE"},
		{"ta1908","ZCE"},
		{"ta1909","ZCE"},
		{"ta1910","ZCE"},
		{"ta1911","ZCE"},
		{"tal8","ZCE"},
		{"tal9","ZCE"},
		{"wh1901","ZCE"},
		{"wh1903","ZCE"},
		{"wh1905","ZCE"},
		{"wh1907","ZCE"},
		{"wh1909","ZCE"},
		{"wh1911","ZCE"},
		{"whl8","ZCE"},
		{"whl9","ZCE"},
		{"zc1812","ZCE"},
		{"zc1901","ZCE"},
		{"zc1902","ZCE"},
		{"zc1903","ZCE"},
		{"zc1904","ZCE"},
		{"zc1905","ZCE"},
		{"zc1906","ZCE"},
		{"zc1907","ZCE"},
		{"zc1908","ZCE"},
		{"zc1909","ZCE"},
		{"zc1910","ZCE"},
		{"zc1911","ZCE"},
		{"zc1912","ZCE"},
		{"zcl8","ZCE"},
		{"zcl9","ZCE"},
		{"a1901","DCE"},
		{"a1903","DCE"},
		{"a1905","DCE"},
		{"a1907","DCE"},
		{"a1909","DCE"},
		{"a1911","DCE"},
		{"a2001","DCE"},
		{"al8","DCE"},
		{"al9","DCE"},
		{"b1812","DCE"},
		{"b1901","DCE"},
		{"b1902","DCE"},
		{"b1903","DCE"},
		{"b1904","DCE"},
		{"b1905","DCE"},
		{"b1906","DCE"},
		{"b1907","DCE"},
		{"b1908","DCE"},
		{"b1909","DCE"},
		{"b1910","DCE"},
		{"b1911","DCE"},
		{"bb1812","DCE"},
		{"bb1901","DCE"},
		{"bb1902","DCE"},
		{"bb1903","DCE"},
		{"bb1904","DCE"},
		{"bb1905","DCE"},
		{"bb1906","DCE"},
		{"bb1907","DCE"},
		{"bb1908","DCE"},
		{"bb1909","DCE"},
		{"bb1910","DCE"},
		{"bb1911","DCE"},
		{"bbl8","DCE"},
		{"bbl9","DCE"},
		{"bl8","DCE"},
		{"bl9","DCE"},
		{"c1901","DCE"},
		{"c1903","DCE"},
		{"c1905","DCE"},
		{"c1907","DCE"},
		{"c1909","DCE"},
		{"c1911","DCE"},
		{"cl8","DCE"},
		{"cl9","DCE"},
		{"cs1901","DCE"},
		{"cs1903","DCE"},
		{"cs1905","DCE"},
		{"cs1907","DCE"},
		{"cs1909","DCE"},
		{"cs1911","DCE"},
		{"csl8","DCE"},
		{"csl9","DCE"},
		{"eg1906","DCE"},
		{"eg1907","DCE"},
		{"eg1908","DCE"},
		{"eg1909","DCE"},
		{"eg1910","DCE"},
		{"eg1911","DCE"},
		{"egl8","DCE"},
		{"egl9","DCE"},
		{"fb1812","DCE"},
		{"fb1901","DCE"},
		{"fb1902","DCE"},
		{"fb1903","DCE"},
		{"fb1904","DCE"},
		{"fb1905","DCE"},
		{"fb1906","DCE"},
		{"fb1907","DCE"},
		{"fb1908","DCE"},
		{"fb1909","DCE"},
		{"fb1910","DCE"},
		{"fb1911","DCE"},
		{"fbl8","DCE"},
		{"fbl9","DCE"},
		{"i1812","DCE"},
		{"i1901","DCE"},
		{"i1902","DCE"},
		{"i1903","DCE"},
		{"i1904","DCE"},
		{"i1905","DCE"},
		{"i1906","DCE"},
		{"i1907","DCE"},
		{"i1908","DCE"},
		{"i1909","DCE"},
		{"i1910","DCE"},
		{"i1911","DCE"},
		{"il8","DCE"},
		{"il9","DCE"},
		{"j1812","DCE"},
		{"j1901","DCE"},
		{"j1902","DCE"},
		{"j1903","DCE"},
		{"j1904","DCE"},
		{"j1905","DCE"},
		{"j1906","DCE"},
		{"j1907","DCE"},
		{"j1908","DCE"},
		{"j1909","DCE"},
		{"j1910","DCE"},
		{"j1911","DCE"},
		{"jd1812","DCE"},
		{"jd1901","DCE"},
		{"jd1902","DCE"},
		{"jd1903","DCE"},
		{"jd1904","DCE"},
		{"jd1905","DCE"},
		{"jd1906","DCE"},
		{"jd1907","DCE"},
		{"jd1908","DCE"},
		{"jd1909","DCE"},
		{"jd1910","DCE"},
		{"jd1911","DCE"},
		{"jdl8","DCE"},
		{"jdl9","DCE"},
		{"jl8","DCE"},
		{"jl9","DCE"},
		{"jm1812","DCE"},
		{"jm1901","DCE"},
		{"jm1902","DCE"},
		{"jm1903","DCE"},
		{"jm1904","DCE"},
		{"jm1905","DCE"},
		{"jm1906","DCE"},
		{"jm1907","DCE"},
		{"jm1908","DCE"},
		{"jm1909","DCE"},
		{"jm1910","DCE"},
		{"jm1911","DCE"},
		{"jml8","DCE"},
		{"jml9","DCE"},
		{"l1812","DCE"},
		{"l1901","DCE"},
		{"l1902","DCE"},
		{"l1903","DCE"},
		{"l1904","DCE"},
		{"l1905","DCE"},
		{"l1906","DCE"},
		{"l1907","DCE"},
		{"l1908","DCE"},
		{"l1909","DCE"},
		{"l1910","DCE"},
		{"l1911","DCE"},
		{"ll8","DCE"},
		{"ll9","DCE"},
		{"m1812","DCE"},
		{"m1901","DCE"},
		{"m1903","DCE"},
		{"m1905","DCE"},
		{"m1907","DCE"},
		{"m1908","DCE"},
		{"m1909","DCE"},
		{"m1911","DCE"},
		{"ml8","DCE"},
		{"ml9","DCE"},
		{"p1812","DCE"},
		{"p1901","DCE"},
		{"p1902","DCE"},
		{"p1903","DCE"},
		{"p1904","DCE"},
		{"p1905","DCE"},
		{"p1906","DCE"},
		{"p1907","DCE"},
		{"p1908","DCE"},
		{"p1909","DCE"},
		{"p1910","DCE"},
		{"p1911","DCE"},
		{"pl8","DCE"},
		{"pl9","DCE"},
		{"pp1812","DCE"},
		{"pp1901","DCE"},
		{"pp1902","DCE"},
		{"pp1903","DCE"},
		{"pp1904","DCE"},
		{"pp1905","DCE"},
		{"pp1906","DCE"},
		{"pp1907","DCE"},
		{"pp1908","DCE"},
		{"pp1909","DCE"},
		{"pp1910","DCE"},
		{"pp1911","DCE"},
		{"ppl8","DCE"},
		{"ppl9","DCE"},
		{"v1812","DCE"},
		{"v1901","DCE"},
		{"v1902","DCE"},
		{"v1903","DCE"},
		{"v1904","DCE"},
		{"v1905","DCE"},
		{"v1906","DCE"},
		{"v1907","DCE"},
		{"v1908","DCE"},
		{"v1909","DCE"},
		{"v1910","DCE"},
		{"v1911","DCE"},
		{"vl8","DCE"},
		{"vl9","DCE"},
		{"y1812","DCE"},
		{"y1901","DCE"},
		{"y1903","DCE"},
		{"y1905","DCE"},
		{"y1907","DCE"},
		{"y1908","DCE"},
		{"y1909","DCE"},
		{"y1911","DCE"},
		{"yl8","DCE"},
		{"yl9","DCE"},
		{"ag1812","SHFE"},
		{"ag1901","SHFE"},
		{"ag1902","SHFE"},
		{"ag1903","SHFE"},
		{"ag1904","SHFE"},
		{"ag1905","SHFE"},
		{"ag1906","SHFE"},
		{"ag1907","SHFE"},
		{"ag1908","SHFE"},
		{"ag1909","SHFE"},
		{"ag1910","SHFE"},
		{"ag1911","SHFE"},
		{"agl8","SHFE"},
		{"agl9","SHFE"},
		{"al1812","SHFE"},
		{"al1901","SHFE"},
		{"al1902","SHFE"},
		{"al1903","SHFE"},
		{"al1904","SHFE"},
		{"al1905","SHFE"},
		{"al1906","SHFE"},
		{"al1907","SHFE"},
		{"al1908","SHFE"},
		{"al1909","SHFE"},
		{"al1910","SHFE"},
		{"al1911","SHFE"},
		{"all8","SHFE"},
		{"all9","SHFE"},
		{"au1812","SHFE"},
		{"au1901","SHFE"},
		{"au1902","SHFE"},
		{"au1904","SHFE"},
		{"au1906","SHFE"},
		{"au1908","SHFE"},
		{"au1910","SHFE"},
		{"au1912","SHFE"},
		{"aul8","SHFE"},
		{"aul9","SHFE"},
		{"bu1812","SHFE"},
		{"bu1901","SHFE"},
		{"bu1902","SHFE"},
		{"bu1903","SHFE"},
		{"bu1904","SHFE"},
		{"bu1905","SHFE"},
		{"bu1906","SHFE"},
		{"bu1909","SHFE"},
		{"bu1912","SHFE"},
		{"bu2003","SHFE"},
		{"bu2006","SHFE"},
		{"bu2009","SHFE"},
		{"bul8","SHFE"},
		{"bul9","SHFE"},
		{"cu1812","SHFE"},
		{"cu1901","SHFE"},
		{"cu1902","SHFE"},
		{"cu1903","SHFE"},
		{"cu1904","SHFE"},
		{"cu1905","SHFE"},
		{"cu1906","SHFE"},
		{"cu1907","SHFE"},
		{"cu1908","SHFE"},
		{"cu1909","SHFE"},
		{"cu1910","SHFE"},
		{"cu1911","SHFE"},
		{"cul8","SHFE"},
		{"cul9","SHFE"},
		{"fu1901","SHFE"},
		{"fu1902","SHFE"},
		{"fu1903","SHFE"},
		{"fu1904","SHFE"},
		{"fu1905","SHFE"},
		{"fu1906","SHFE"},
		{"fu1907","SHFE"},
		{"fu1908","SHFE"},
		{"fu1909","SHFE"},
		{"fu1910","SHFE"},
		{"fu1911","SHFE"},
		{"fu1912","SHFE"},
		{"ful8","SHFE"},
		{"ful9","SHFE"},
		{"hc1812","SHFE"},
		{"hc1901","SHFE"},
		{"hc1902","SHFE"},
		{"hc1903","SHFE"},
		{"hc1904","SHFE"},
		{"hc1905","SHFE"},
		{"hc1906","SHFE"},
		{"hc1907","SHFE"},
		{"hc1908","SHFE"},
		{"hc1909","SHFE"},
		{"hc1910","SHFE"},
		{"hc1911","SHFE"},
		{"hcl8","SHFE"},
		{"hcl9","SHFE"},
		{"ni1812","SHFE"},
		{"ni1901","SHFE"},
		{"ni1902","SHFE"},
		{"ni1903","SHFE"},
		{"ni1904","SHFE"},
		{"ni1905","SHFE"},
		{"ni1906","SHFE"},
		{"ni1907","SHFE"},
		{"ni1908","SHFE"},
		{"ni1909","SHFE"},
		{"ni1910","SHFE"},
		{"ni1911","SHFE"},
		{"nil8","SHFE"},
		{"nil9","SHFE"},
		{"pb1812","SHFE"},
		{"pb1901","SHFE"},
		{"pb1902","SHFE"},
		{"pb1903","SHFE"},
		{"pb1904","SHFE"},
		{"pb1905","SHFE"},
		{"pb1906","SHFE"},
		{"pb1907","SHFE"},
		{"pb1908","SHFE"},
		{"pb1909","SHFE"},
		{"pb1910","SHFE"},
		{"pb1911","SHFE"},
		{"pbl8","SHFE"},
		{"pbl9","SHFE"},
		{"rb1812","SHFE"},
		{"rb1901","SHFE"},
		{"rb1902","SHFE"},
		{"rb1903","SHFE"},
		{"rb1904","SHFE"},
		{"rb1905","SHFE"},
		{"rb1906","SHFE"},
		{"rb1907","SHFE"},
		{"rb1908","SHFE"},
		{"rb1909","SHFE"},
		{"rb1910","SHFE"},
		{"rb1911","SHFE"},
		{"rbl8","SHFE"},
		{"rbl9","SHFE"},
		{"ru1901","SHFE"},
		{"ru1903","SHFE"},
		{"ru1904","SHFE"},
		{"ru1905","SHFE"},
		{"ru1906","SHFE"},
		{"ru1907","SHFE"},
		{"ru1908","SHFE"},
		{"ru1909","SHFE"},
		{"ru1910","SHFE"},
		{"ru1911","SHFE"},
		{"rul8","SHFE"},
		{"rul9","SHFE"},
		{"sc1901","SHFE"},
		{"sc1902","SHFE"},
		{"sc1903","SHFE"},
		{"sc1904","SHFE"},
		{"sc1905","SHFE"},
		{"sc1906","SHFE"},
		{"sc1907","SHFE"},
		{"sc1908","SHFE"},
		{"sc1909","SHFE"},
		{"sc1910","SHFE"},
		{"sc1911","SHFE"},
		{"sc1912","SHFE"},
		{"sc2003","SHFE"},
		{"sc2006","SHFE"},
		{"sc2009","SHFE"},
		{"sc2012","SHFE"},
		{"sc2103","SHFE"},
		{"sc2106","SHFE"},
		{"sc2109","SHFE"},
		{"sc2112","SHFE"},
		{"scl8","SHFE"},
		{"scl9","SHFE"},
		{"sn1812","SHFE"},
		{"ap1812","ZCE"},
		{"ap1901","ZCE"},
		{"ap1903","ZCE"},
		{"ap1905","ZCE"},
		{"ap1907","ZCE"},
		{"ap1910","ZCE"},
		{"ap1911","ZCE"},
		{"apl8","ZCE"},
		{"apl9","ZCE"},
		{"cf1901","ZCE"},
		{"cf1903","ZCE"},
		{"cf1905","ZCE"},
		{"cf1907","ZCE"},
		{"cf1909","ZCE"},
		{"cf1911","ZCE"},
		{"cfl8","ZCE"},
		{"cfl9","ZCE"},
		{"cy1812","ZCE"},
		{"cy1901","ZCE"},
		{"cy1902","ZCE"},
		{"cy1903","ZCE"},
		{"cy1904","ZCE"},
		{"cy1905","ZCE"},
		{"cy1906","ZCE"},
		{"cy1907","ZCE"},
		{"cy1908","ZCE"},
		{"cy1909","ZCE"},
		{"cy1910","ZCE"},
		{"cy1911","ZCE"},
		{"cyl8","ZCE"},
		{"cyl9","ZCE"},
		{"fg1812","ZCE"},
		{"fg1901","ZCE"},
		{"fg1902","ZCE"},
		{"fg1903","ZCE"},
		{"fg1904","ZCE"},
		{"fg1905","ZCE"},
		{"fg1906","ZCE"},
		{"fg1907","ZCE"},
		{"fg1908","ZCE"},
		{"fg1909","ZCE"},
		{"fg1910","ZCE"},
		{"fg1911","ZCE"},
		{"fgl8","ZCE"},
		{"fgl9","ZCE"},
		{"jr1901","ZCE"},
		{"jr1903","ZCE"},
		{"jr1905","ZCE"},
		{"jr1907","ZCE"},
		{"jr1909","ZCE"},
		{"jr1911","ZCE"},
		{"jrl8","ZCE"},
		{"jrl9","ZCE"},
		{"lr1901","ZCE"},
		{"lr1903","ZCE"},
		{"lr1905","ZCE"},
		{"lr1907","ZCE"},
		{"lr1909","ZCE"},
		{"lr1911","ZCE"},
		{"lrl8","ZCE"},
		{"lrl9","ZCE"},
		{"ma1812","ZCE"},
		{"ma1901","ZCE"},
		{"ic1812","CFFEX"},
		{"ic1901","CFFEX"},
		{"ic1903","CFFEX"},
		{"ic1906","CFFEX"},
		{"ic500","CFFEX"},
		{"icl8","CFFEX"},
		{"icl9","CFFEX"},
		{"if1812","CFFEX"},
		{"if1901","CFFEX"},
		{"if1903","CFFEX"},
		{"if1906","CFFEX"},
		{"ifshfe0","CFFEX"},
		{"ifl0","CFFEX"},
		{"ifl1","CFFEX"},
		{"ifl2","CFFEX"},
		{"ifl3","CFFEX"},
		{"ifl8","CFFEX"},
		{"ifl9","CFFEX"},
		{"ih1812","CFFEX"},
		{"ih1901","CFFEX"},
		{"ih1903","CFFEX"},
		{"ih1906","CFFEX"},
		{"ih50","CFFEX"},
		{"ihl8","CFFEX"},
		{"ihl9","CFFEX"},
		{"t1812","CFFEX"},
		{"t1903","CFFEX"},
		{"t1906","CFFEX"},
		{"tf1812","CFFEX"},
		{"tf1903","CFFEX"},
		{"tf1906","CFFEX"},
		{"tfl0","CFFEX"},
		{"tfl1","CFFEX"},
		{"tfl2","CFFEX"},
		{"tfl8","CFFEX"},
		{"tfl9","CFFEX"},
		{"tl8","CFFEX"},
		{"tl9","CFFEX"},
		{"ts1812","CFFEX"},
		{"ts1903","CFFEX"},
		{"ts1906","CFFEX"},
		{"tsl8","CFFEX"},
		{"tsl9,CFFEX"}
	};*/

}