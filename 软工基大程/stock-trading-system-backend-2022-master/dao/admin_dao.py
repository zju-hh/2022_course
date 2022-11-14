from exts import db
from model.admin import Admin
from model.admin_permission import AdminPermission
from model.center_trade import Stock


# 将一个表的所有简单操作集中成一个dao数据库类
class AdminDao:
    @staticmethod
    def insert(admins):
        db.session.add_all(admins)
        db.session.commit()

    @staticmethod
    def get(admin_id):
        admin = Admin.query.get(admin_id)
        return admin

    @staticmethod
    def update(admin_id, new_password):
        admin = Admin.query.get(admin_id)
        admin.password = new_password
        db.session.commit()

