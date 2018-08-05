//
// Created by Yu Yang Zhang on 6/9/18.
//

#include "global_square.hpp"
#include <eosio.token/eosio.token.hpp>

void global_square::setinfo(account_name account, string &avatar, string &full_image, string &website, string &facebook,
						   string &twitter, string &medium, string &steemit, string &telegram, string &github,
						   string &organization) {
	require_auth(account);
	eosio::print("account is ", name{account}, "\n");

	global_square::accountinfo accountinfo(_self, account);

	auto itr = accountinfo.find(account);

	if (itr == accountinfo.end()) {
		accountinfo.emplace(account, [&](auto &p) {
			p.account = account;
			p.avatar = avatar;
			p.full_image = full_image;
			p.website = website;
			p.facebook = facebook;
			p.twitter = twitter;
			p.medium = medium;
			p.steemit = steemit;
			p.telegram = telegram;
			p.github = github;
			p.organization = organization;
			print("new organization is ", p.organization, "\n");
		});
	} else {
		accountinfo.modify(itr, itr->account, [&](auto &p) {
			print("origin organization is ", p.organization, "\n");
			p.account = account;
			p.avatar = avatar;
			p.full_image = full_image;
			p.website = website;
			p.facebook = facebook;
			p.twitter = twitter;
			p.medium = medium;
			p.steemit = steemit;
			p.telegram = telegram;
			p.github = github;
			p.organization = organization;

			print("update organization is ", p.organization, "\n");
		});
	}
}

void global_square::create(account_name issuer,
						  asset maximum_supply) {
	require_auth(_self);

	auto sym = maximum_supply.symbol;
	eosio_assert(sym.is_valid(), "invalid symbol name");
	eosio_assert(maximum_supply.is_valid(), "invalid supply");
	eosio_assert(maximum_supply.amount > 0, "max-supply must be positive");

	stats stattable(_self, sym.name());
	auto existing = stattable.find(sym.name());
	eosio_assert(existing == stattable.end(), "token with symbol already exists");

	stattable.emplace(_self, [&](auto &s) {
		s.supply.symbol = maximum_supply.symbol;
		s.max_supply = maximum_supply;
		s.issuer = issuer;
	});
}


void global_square::buyarea(account_name buyer, uint64_t price_per_square) {
	areastat areatable(_self, _self);

	print("buy area..");

	areatable.emplace(buyer, [&](auto &a) {
		a.area_id = areatable.available_primary_key();
		a.owner = buyer;
		a.price_per_square = price_per_square;
		a.rented = 0;
	});

	INLINE_ACTION_SENDER(eosio::token, transfer)(N(eosio.token), {buyer, N(active)},
												 {buyer, N(globalsquare), asset(5),
												  std::string("buy area fee")});
}


void global_square::rentareas(account_name renter, vector<uint64_t> areas) {

	renterstat rentertable(_self, _self);
	areastat areatable(_self, _self);

	auto itr = rentertable.find(renter);
	if (itr == rentertable.end()) {
		rentertable.emplace(renter, [&](auto &r) {
			r.renter = renter;
			for (auto area: areas) {
				r.areas.push_back(area);
			}

		});

		for (auto area: areas) {
			auto itr_price = areatable.find(area);
			if (itr_price == areatable.end()) {}
			else {
				areatable.modify(itr_price, _self, [&](auto &a) {
					a.rented = 1;
				});
				INLINE_ACTION_SENDER(eosio::token, transfer)(N(eosio.token), {renter, N(active)},
															 {renter, N(inita1111111), asset(5),
															  std::string("rent fee")});
			}
		}
	} else {
		rentertable.modify(itr, itr->renter, [&](auto &r) {
			for (auto area: areas) {
				r.areas.push_back(area);
			}
		});

		for (auto area: areas) {
			auto itr_price = areatable.find(area);
			if (itr_price == areatable.end()) {}
			else {
				areatable.modify(itr_price, _self, [&](auto &a) {
					a.rented = 1;
				});
				INLINE_ACTION_SENDER(eosio::token, transfer)(N(eosio.token), {renter, N(active)},
															 {renter, N(renter), asset(5),
															  std::string("rent fee")});
			}
		}
	}
}


void global_square::payplant(uint64_t area, account_name payer, account_name renter) {
	areastat areatable(_self, _self);

	print("pay plant success...");
	auto itr = areatable.find(area);
	if (itr == areatable.end()) {}
	else {
		INLINE_ACTION_SENDER(eosio::token, transfer)(N(eosio.token), {payer, N(active)},
													 {payer, renter, asset(50000),
													  std::string("plant fee")});
	}
}

void global_square::paywater(uint64_t area, account_name payer, account_name renter) {
	areastat areatable(_self, _self);
	print("pay water success...");

	auto itr = areatable.find(area);
	if (itr == areatable.end()) {}
	else {
		INLINE_ACTION_SENDER(eosio::token, transfer)(N(eosio.token), {payer, N(active)},
													 {payer, renter, asset(20000),
													  std::string("water fee")});
	}
}


EOSIO_ABI(global_square, (setinfo)(create)(rentareas)(buyarea)(payplant)(paywater))