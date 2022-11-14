from dao.agg_auc_dao import AggAucDao
from model.center_trade import Instruction
from model.center_trade import K
from model.center_trade import Stock
import time
import datetime


class AggAuc:
    @staticmethod
    def aggregate_auction():
        s_id = AggAucDao.getstockid()
        t_record = []  # 总的交易记录列表
        r_last_cnt = 0  # 记录表中之前的项数
        for sid in s_id:
            buy = AggAucDao.getbuyinstr(sid)     # 买指令价格从高到低排序
            sell = AggAucDao.getsellinstr(sid)   # 卖指令价格从低到高排序
            bf = 0  # 买指令index
            sf = 0  # 卖指令index
            # 买卖指令都存在时
            while bf < len(buy) and sf < len(sell):
                b = buy[bf]
                s = sell[sf]
                price = 0.0
                # 买价>=卖价，可以撮合
                if b.target_price >= s.target_price:
                    min_num = min(b.target_number, s.target_number)
                    price = 0.5 * (b.target_price + s.target_price)  # 中间价格计算
                    record = [b.instruction_id, s.instruction_id, min_num]  # 暂时先不插入最终成交价格
                    t_record.append(record)  # 将记录加入总表
                    b.target_number = b.target_number - min_num  # 更新股票数量
                    s.target_number = s.target_number - min_num
                    if b.target_number == 0:  # 指针后移
                        bf = bf + 1
                    if s.target_number == 0:
                        sf = sf + 1
                # 买价<卖价，撮合结束
                else:
                    break
            for i in range(r_last_cnt, len(t_record)):
                t_record[i].append(price)  # 插入最终的成交价
            r_last_cnt = len(t_record)
        return t_record

    @staticmethod
    def update(t_id):
        # update stock price
        t_price = AggAucDao.gettransprice(t_id)
        s_id = AggAucDao.getstockid(t_id)
        AggAucDao.updatestockprice(s_id, t_price)

        # update K table
        date = AggAucDao.getstockid(t_id)
        k_info = AggAucDao.getkinfo(s_id, date)
        h_pri = k_info.highest_price
        l_pri = k_info.lowest_price
        k_id = k_info.k_id

        if(h_pri == None):
            AggAucDao.updatestartprice(k_id, t_price)

        AggAucDao.updateendprice(k_id, t_price)

        if(t_price > h_pri or h_pri == None):
            AggAucDao.updatehighestprice(k_id, t_price)

        if(t_price < l_pri or l_pri == None):
            AggAucDao.updatelowestprice(k_id, t_price)

        # update instruction
        i_id = AggAucDao.getinstid(t_id)
        t_number = AggAucDao.getinstnumber(t_id)
        t_amount = AggAucDao.getinstamount(t_id)
        AggAucDao.updateinstinfo(i_id, t_number, t_amount)

        i_info = AggAucDao.getinstinfo(i_id)
        t_num = i_info.target_number
        a_num = i_info.actual_number

        if(t_num == a_num):
            flag = 'T'
        else:
            flag = 'P'

        AggAucDao.updateinsttype(i_id, flag)

    # 获取日期时间
    @staticmethod
    def getnowdata():
        now = datetime.datetime.now()
        s = now.strftime('%Y%m%d')
        data = int(s, 10)
        return data

    @staticmethod
    def getnowtime():
        now = datetime.datetime.now()
        s = now.strftime('%H%M%S')
        time = int(s, 10)
        return time

    # 生成交易结果
    @staticmethod
    def createtransres(con_res):
        b_id = con_res[0]
        s_id = con_res[1]
        t_price = con_res[3]
        t_number = con_res[2]
        stock_id = AggAucDao.gettransstock(b_id)
        b_s_flag1 = AggAucDao.gettransflag(b_id)
        b_s_flag2 = AggAucDao.gettransflag(s_id)
        a_number1 = AggAucDao.gettransaccount(b_id)
        a_number2 = AggAucDao.gettransaccount(s_id)
        t_amount = t_price * t_number
        t_date = AggAucDao.getnowdata()
        t_time = AggAucDao.getnowtime()
        i_id1 = AggAucDao.gettransinstr(b_id)
        i_id2 = AggAucDao.gettransinstr(s_id)
        t1_id = AggAucDao.updatetransinfo(stock_id, b_s_flag1, a_number1, t_price,
                                          t_amount, t_number, t_date, t_time, i_id1)
        t2_id = AggAucDao.updatetransinfo(stock_id, b_s_flag2, a_number2, t_price,
                                          t_amount, t_number, t_date, t_time, i_id2)
        t_id = [t1_id, t2_id]
        return t_id

    @staticmethod
    def deal_expired_instruction():         # 处理过期指令
        AggAucDao.dealexpins()

    @staticmethod
    def create_k_table():       # 创建k值表
        AggAucDao.createktable()

    # 判断股票状态
    @staticmethod
    def judge_stock_status():
        localtime = time.asctime(time.localtime(time.time()))
        localtime = time.strftime("%Y%m%d", time.localtime())
        inttime = int(localtime)
        instr = AggAucDao.gettodayins()
        for i in instr:
            s = AggAucDao.getstock(i)                      # 获取股票信息
            if s.stock_status=='F':                        # 股票状态为'F',无法交易
                AggAucDao.setexp(i.instruction_id)         # 设置指令为过期指令


    #判断涨跌幅
    @staticmethod
    def judge_rise_fall():
        instr = AggAucDao.gettodayins()
        for i in instr:
            s = AggAucDao.getstock(i.instruction_id)              # 获取股票信息
            k = AggAucDao.getyesterdayk(s.stock_id)               # 获取昨日K值表
            if i.target_price>(k.end_price)*(1+s.rise_threshold) or i.target_price<(k.end_price)*(1-s.fall_threshold):
                AggAucDao.setexp(i.instruction_id) # 出价不在涨跌幅范围内

    @staticmethod
    def aggregate_instruction_pretreatment():
        AggAucDao.dealexpins()  # 处理过期指令
        AggAucDao.createktable()  # 创建K值表

        # 判断股票状态
        localtime = time.strftime("%Y%m%d", time.localtime())
        inttime = int(localtime)
        instr = AggAucDao.gettodayins()
        for i in instr:
            s = AggAucDao.getstock(i)  # 获取股票信息
            if s.stock_status == 'F':  # 股票状态为'F',无法交易
                AggAucDao.setexp(i.instruction_id)  # 设置指令为过期指令

        # 判断涨跌幅
        instr = AggAucDao.gettodayins()
        for i in instr:
            s = AggAucDao.getstock(i.instruction_id)  # 获取股票信息
            k = AggAucDao.getyesterdayk(s.stock_id)  # 获取昨日K值表
            if i.target_price > (k.end_price) * (1 + s.rise_threshold) or i.target_price < (k.end_price) * (
                    1 - s.fall_threshold):
                AggAucDao.setexp(i.instruction_id)  # 出价不在涨跌幅范围内，标记指令过期
                