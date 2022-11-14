from exts import db


class AccountAdmin(db.Model):
    __tablename__ = "administrator_account"
    administrator_id = db.Column(db.String(20), nullable=False, primary_key=True)
    administrator_password = db.Column(db.String(200), nullable=False)


class Deal(db.Model):
    __tablename__ = "deal"
    deal_id = db.Column(db.Integer, nullable=False, primary_key=True)
    securities_account_number = db.Column(db.String(20), nullable=False)
    person_id = db.Column(db.String(18), nullable=False)
    status = db.Column(db.String(10), nullable=False)
    event = db.Column(db.String(10), nullable=False)


class LegalPersonSecuritiesAccount(db.Model):
    __tablename__ = "legal_person_securities_account"
    l_account_number = db.Column(db.String(20), nullable=False, primary_key=True)
    password = db.Column(db.String(200), nullable=False)
    legal_person_registration_number = db.Column(db.String(18), nullable=False)
    business_license_number = db.Column(db.String(15), nullable=False)
    legal_person_id_number = db.Column(db.String(18), nullable=False)
    legal_person_name = db.Column(db.String(50), nullable=False)
    legal_person_telephone = db.Column(db.String(11), nullable=False)
    legal_person_address = db.Column(db.String(100), nullable=False)
    excutor = db.Column(db.String(50), nullable=False)
    authorized_person_id_number = db.Column(db.String(18), nullable=False)
    authorized_person_telephone = db.Column(db.String(11), nullable=False)
    authorized_person_address = db.Column(db.String(100), nullable=False)
    authority = db.Column(db.String(3), nullable=False)
    status = db.Column(db.String(2), nullable=False)


class PersonalSecuritiesAccount(db.Model):
    __tablename__ = "personal_securities_account"
    p_account_number = db.Column(db.String(20), nullable=False, primary_key=True)
    password = db.Column(db.String(200), nullable=False)
    user_name = db.Column(db.String(50), nullable=False)
    user_gender = db.Column(db.String(1), nullable=False)
    registration_date = db.Column(db.Integer, nullable=False)
    user_id_number = db.Column(db.String(18), nullable=False)
    user_address = db.Column(db.String(100), nullable=False)
    user_job = db.Column(db.String(100), nullable=False)
    user_education = db.Column(db.String(20), nullable=False)
    user_work_unit = db.Column(db.String(100), nullable=False)
    telephone = db.Column(db.String(11), nullable=False)
    agent = db.Column(db.Boolean, nullable=False)
    agent_id = db.Column(db.String(18))
    authority = db.Column(db.String(3))
    status = db.Column(db.String(2), nullable=False)


class FundAccount(db.Model):
    __tablename__ = "fund_account"
    fund_account_number = db.Column(db.String(20), nullable=False, primary_key=True)
    balance = db.Column(db.Float, nullable=False)
    frozen = db.Column(db.Float, nullable=False)
    taken = db.Column(db.Float, nullable=False)
    trade_password = db.Column(db.String(200), nullable=False)
    login_password = db.Column(db.String(200), nullable=False)
    account_status = db.Column(db.String(4), nullable=False)
    securities_account_number = db.Column(db.String(20), nullable=False)


class OwnStock(db.Model):
    __tablename__ = "own_stock"
    stock_id = db.Column(db.String(20), nullable=False, primary_key=True)
    securities_account_number = db.Column(db.String(20), nullable=False, primary_key=True)
    own_number = db.Column(db.Integer, nullable=False)
    frozen = db.Column(db.Integer, nullable=False)
    own_amount = db.Column(db.Float, nullable=False)
