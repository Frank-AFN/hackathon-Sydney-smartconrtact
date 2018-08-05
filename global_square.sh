# part I
cleos system newaccount eosio globalsquare EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV --stake-net "10.0000 SYS" --stake-cpu "10.0000 SYS" --buy-ram "10.0000 SYS"
cleos set contract globalsquare $EOS_BUILD_DIR/contracts/global_square/ -p globalsquare

# cleos set account permission inita1111111 active '{"threshold": 1,"keys": [{"key":"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV", "weight":1}],"accounts": [{"permission":{"actor":"globalsquare","permission":"eosio.code"},"weight":1}]}' owner -p inita1111111
# cleos set account permission initb1111111 active '{"threshold": 1,"keys": [{"key":"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV", "weight":1}],"accounts": [{"permission":{"actor":"globalsquare","permission":"eosio.code"},"weight":1}]}' owner -p initb1111111
# cleos set account permission eosiosg11111 active '{"threshold": 1,"keys": [{"key":"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV", "weight":1}],"accounts": [{"permission":{"actor":"globalsquare","permission":"eosio.code"},"weight":1}]}' owner -p eosiosg11111

cleos push action eosio updateauth '["inita1111111","active","owner",
{"threshold":1,"keys":[{"key":"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight":1}],
"waits":[],"accounts":[{"weight":1,"permission":{"actor":"globalsquare","permission":"eosio.code"}}]}]' -p inita1111111

cleos push action eosio updateauth '["initb1111111","active","owner",
{"threshold":1,"keys":[{"key":"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight":1}],
"waits":[],"accounts":[{"weight":1,"permission":{"actor":"globalsquare","permission":"eosio.code"}}]}]' -p initb1111111


cleos push action globalsquare buyarea '{
	"buyer": "inita1111111",
	"price_per_square": 5
}' -p inita1111111

cleos push action globalsquare buyarea '{
	"buyer": "inita1111111",
	"price_per_square": 6
}' -p inita1111111


cleos push action globalsquare rentareas '{
	"renter": "initb1111111",
	"areas":[0],
}' -p initb1111111

cleos push action globalsquare payplant '{
	"area": 0,
	"payer": "inita1111111",
	"renter": "initb1111111"
}' -p initb1111111


cleos push action globalsquare paywater '{
	"area": 0,
	"payer": "inita1111111",
	"renter": "initb1111111"
}' -p initb1111111



# cleos push action globalsquare setinfo '{
#  "account": "eosiosg11111",
#  "avatar": "http://www.eosio.sg/thumbnail.png",
#  "full_image": "http://www.eosio.sg/image.ong",
#  "organization": "EOSIO.SG",
#  "website": "http://www.eosio.sg",
#  "facebook": "http://www.facebook.comn/eosiosg",
#  "twitter": "http://www.twitter.com/eosiosg",
#  "medium": "http://www.medium.com/eosiosg",
#  "steemit": "http://www.medium.com/eosiosg",
#  "telegram": "http://",
#  "github": "http://www.github.io/eosiosg"
# }' -p eosiosg11111


# cleos push action globalsquare setinfo '{
#  "account": "inita1111111",
#  "avatar": "http://www.eosio.sg/thumbnail.png",
#  "full_image": "http://www.eosio.sg/image.ong",
#  "organization": "EOSIO.SG",
#  "website": "http://www.eosio.sg",
#  "facebook": "http://www.facebook.comn/eosiosg",
#  "twitter": "http://www.twitter.com/eosiosg",
#  "medium": "http://www.medium.com/eosiosg",
#  "steemit": "http://www.medium.com/eosiosg",
#  "telegram": "http://t.me/eosiosg",
#  "github": "http://www.github.io/eosiosg"
# }' -p inita1111111

# cleos push action globalsquare setinfo '{
#  "account": "initb1111111",
#  "avatar": "http://www.eosio.sg/thumbnail.png",
#  "full_image": "http://www.eosio.sg/image.ong",
#  "organization": "EOSIO.SG",
#  "website": "http://www.eosio.sg",
#  "facebook": "http://www.facebook.comn/eosiosg",
#  "twitter": "http://www.twitter.com/eosiosg",
#  "medium": "http://www.medium.com/eosiosg",
#  "steemit": "http://www.medium.com/eosiosg",
#  "telegram": "http://t.me/eosiosg",
#  "github": "http://www.github.io/eosiosg"
# }' -p initb1111111

# cleos push action globalsquare setinfo '{
#  "account": "initb1111111",
#  "avatar": "http://www.eosio.sg/thumbnail.png",
#  "full_image": "http://www.eosio.sg/image.ong",
#  "organization": "EOSIO.SG",
#  "website": "http://www.eosio.sg",
#  "facebook": "http://www./eosiosg",
#  "twitter": "http://www.twer.com/eosiosg",
#  "medium": "http://www.medium.com/eosiosg",
#  "steemit": "http://www.medium.com/eosiosg",
#  "telegram": "http://t.me/eosiosg",
#  "github": "http://www.github.io/eosiosg"
# }' -p initb1111111

# cleos push action globalsquare regfollower '{"followee": "initb1111111", "follower": "inita1111111", "pub_key":"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV"}' -p inita1111111 initb1111111
# cleos push action globalsquare regfollower '{"followee": "initb1111111", "follower": "eosiosg11111", "pub_key":"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV"}' -p eosiosg11111 initb1111111


# cleos get table globalsquare inita1111111 accountinfo
# cleos get table globalsquare initb1111111 accountinfo
# cleos get table globalsquare eosiosg11111 accountinfo


# # part II

cleos get table globalsquare globalsquare areastat

cleos get table globalsquare globalsquare renterstat












