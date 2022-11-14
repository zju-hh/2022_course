from exts import db
from model.center_trade import Instruction
from model.center_trade import K
from model.center_trade import Stock
from model.center_trade import Transaction
from sqlalchemy import and_
import time

class ConInsPreDao:

    #获取昨日K值表
    @staticmethod
    def getyesterdayk(stock_id):
        localtime = time.asctime(time.localtime(time.time()))
        localtime = time.strftime("%Y%m%d", time.localtime())
        inttime = int(localtime)
        tmpk = K.query.filter(_and(K.stock_id == i.stock_id, K.date < inttime))
        tmpk = tmpk.query.order_by(desc("date")).first()
        return tmpk

    #获取股票信息
    @staticmethod
    def getstock(ins):
        s = Stock.query.filter(Stock.stock_id == ins.stock_id)
        return s

    #获取指令信息
    @staticmethod
    def getins(ins_id):
        ins = Instruction.query.filter(Instruction.instruction.id == ins_id)
        return

    #设置不在涨跌幅阈值内的指令为过期指令
    @staticmethod
    def setexp(ins_id):
        ins = Instruction.query.filter(Instruction.instruction_id == ins_id)
        ins.instruction_state == "E"
        db.session.commit()