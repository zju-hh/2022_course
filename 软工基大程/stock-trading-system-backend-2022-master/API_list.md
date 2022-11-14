# API_list

## A1组负责



## A2组负责



## A3组负责



## A4组负责


### POST /release_search

普通查询，返回股票基本信息、今日价格信息、最近交易信息的字典

request body:

```json
{
    "content": "test"
}
```

response body:

```json
{
    "code": 0,
    "data": [
        {
            "buy_sell_flag": "B",
            "end_price": 8.0,
            "highest_price": 10.0,
            "lowest_price": 3.0,
            "start_price": 5.0,
            "stock_id": "a111",
            "stock_name": "test1",
            "transaction_amount": 50.0,
            "transaction_date": 20220526,
            "transaction_number": 10,
            "transaction_price": 5.0,
            "transaction_time": 162600
        },
        {
            "buy_sell_flag": "B",
            "end_price": 8.0,
            "highest_price": 10.0,
            "lowest_price": 3.0,
            "start_price": 5.0,
            "stock_id": "a111",
            "stock_name": "test1",
            "transaction_amount": 35.0,
            "transaction_date": 20220526,
            "transaction_number": 70,
            "transaction_price": 5.0,
            "transaction_time": 162800
        },
        {
            "buy_sell_flag": "B",
            "end_price": 8.0,
            "highest_price": 10.0,
            "lowest_price": 3.0,
            "start_price": 5.0,
            "stock_id": "a111",
            "stock_name": "test1",
            "transaction_amount": 35.0,
            "transaction_date": 20220525,
            "transaction_number": 70,
            "transaction_price": 5.0,
            "transaction_time": 161800
        },
        {
            "buy_sell_flag": "B",
            "end_price": 8.0,
            "highest_price": 10.0,
            "lowest_price": 3.0,
            "start_price": 5.0,
            "stock_id": "a111",
            "stock_name": "test1",
            "transaction_amount": 35.0,
            "transaction_date": 20220524,
            "transaction_number": 70,
            "transaction_price": 5.0,
            "transaction_time": 161800
        },
        {
            "buy_sell_flag": "B",
            "end_price": 4.0,
            "highest_price": 5.0,
            "lowest_price": 1.0,
            "start_price": 2.0,
            "stock_id": "a112",
            "stock_name": "test2",
            "transaction_amount": 35.0,
            "transaction_date": 20220525,
            "transaction_number": 70,
            "transaction_price": 5.0,
            "transaction_time": 161800
        }
    ],
    "message": "success"
}
```

### POST /release_search_advanced

付费用户查询，传入股票id，返回股票每天的开票价、收盘价、最高价、最低价

request body:

```json
{
    "content":"a111"
}
```

```json
{
    "code": 0,
    "data": [
        {
            "date": 20220526,
            "end_price": 8.0,
            "highest_price": 10.0,
            "lowest_price": 3.0,
            "start_price": 5.0
        },
        {
            "date": 20220525,
            "end_price": 9.0,
            "highest_price": 10.0,
            "lowest_price": 3.0,
            "start_price": 7.0
        }
    ],
    "message": "success"
}
```


## A5组负责

除登录和注册外，其他请求需要携带Header: `Authorization`，表示用户登录后的身份认证，值为token值。

### POST /admin/login

登录股票管理员用户，返回token。

request body: 

```json
{
    "admin_id": "beet",
    "password": "123456"
}
```

response body:

```json
{
    "code": 0,
    "data": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJhZG1pbl9pZCI6ImJlZXQiLCJ0eXBlIjoiYWRtaW4iLCJleHAiOjE2NTM1MDM0Mjh9.7B8yU34jAMDVakE6WazvCTUcssnk1QuRo1CCWVh93n4",
    "message": "success"
}
```

### POST /admin

注册股票管理员用户。

request body: 

```json
[
    {
        "admin_id": "haha",
        "password": "123456"
    }
]
```

是一个数组，可以一次性注册多个（前端并不使用这个接口，纯方便用）。

response body:

```json
{
    "code": 0,
    "data": null,
    "message": "success"
}
```

### PUT /admin

服务端会从token中获取你的身份，只需要传输原密码和新密码。

request body:

```json
{
    "password": "123456",
    "new_password": "1234567"
}
```

response body:

```json
{
    "code": 0,
    "data": null,
    "message": "success"
}
```

### GET /admin/permission

获取当前登录管理员的可管理股票列表。

response body:

```json
{
    "code": 0,
    "data": [
        {
            "status": "T",
            "stock_id": "a111",
            "stock_name": "test1"
        },
        {
            "status": "F",
            "stock_id": "a112",
            "stock_name": "test2"
        }
    ],
    "message": "success"
}
```

### PUT /admin/stock_status

修改股票交易状态。

request body:

```json
{
    "stock_id": "a111",
    "stock_status": "F"
}
```

response body:

```json
{
    "code": 0,
    "data": null,
    "message": "success"
}
```

### PUT /admin/stock_threshold

修改股票涨跌幅阈值。

request body:

```json
{
    "stock_id": "a111",
    "rise_threshold": 10,
    "fall_threshold": 10
}
```

response body:

```json
{
    "code": 0,
    "data": null,
    "message": "success"
}
```

### GET /admin/latest_transaction

获取股票最新交易的数量和价格。

request body:

```json
{
    "stock_id": "a111"
}
```

response body:

```json
{
    "code": 0,
    "data": {
        "latest_amount": 2,
        "latest_price": 12.11
    },
    "message": "success"
}
```

### GET /admin/instruction

获取股票交易指令。B表示买，S表示卖

request body:

```json
{
    "buy_or_sell": "B",
    "stock_id": "a111"
}
```

response body:

```json
{
    "code": 0,
    "data": [
        {
            "actual_number": 0,
            "buy_sell_flag": "B",
            "fund_account_number": "a_12345678",
            "instruction_id": "1",
            "instruction_state": "N",
            "stock_id": "a111",
            "target_number": 1,
            "target_price": 1.0,
            "time": 1,
            "total_amount": 0.0
        }
    ],
    "message": "success"
}
```

### 错误代码

若错误代码为102，请跳转回登录界面。其余错误代码只需要alert即可。

正常代码为0。
