//
// Created by Yu Yang Zhang on 6/9/18.
//

#ifndef EOSIO_GLOBAL_SQUARE_HPP
#define EOSIO_GLOBAL_SQUARE_HPP

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>


using namespace eosio;
using namespace std;

class global_square : public eosio::contract {
public:
	global_square(account_name self) : contract(self) {};

private:
	//@abi table
	struct account_info {
		account_name account;
		std::string avatar;
		std::string full_image;
		std::string website;
		std::string facebook;
		std::string twitter;
		std::string medium;
		std::string steemit;
		std::string telegram;
		std::string github;
		std::string organization;
		std::vector<string> follower_keys;

		auto primary_key() const { return account; }

		EOSLIB_SERIALIZE(account_info,
						 (account)(avatar)(full_image)(website)(facebook)(twitter)(medium)(steemit)(telegram)(github)(
								 organization)(follower_keys));
	};

	//@abi table
	struct currency_stat {
		account_name issuer;
		asset supply;
		asset max_supply;

		uint64_t primary_key() const { return issuer; }
	};


	//@abi table
	struct area_stat {
		uint64_t area_id;
		account_name owner;
		uint64_t price_per_square;
		uint32_t rented;

		uint64_t primary_key() const { return area_id; }
		EOSLIB_SERIALIZE(area_stat, (area_id)(owner)(price_per_square)(rented));
	};

	//@abi table
	struct renter_stat{
		account_name renter;
		std::vector<uint64_t> areas;

		uint64_t primary_key() const { return renter; }
		EOSLIB_SERIALIZE(renter_stat, (renter)(areas));

	};

	typedef eosio::multi_index<N(stat), currency_stat> stats;
	typedef eosio::multi_index<N(renterstat), renter_stat> renterstat;
	typedef eosio::multi_index<N(areastat), area_stat> areastat;

	typedef eosio::multi_index<N(accountinfo), account_info> accountinfo;


public:
	//@abi action
	void setinfo(account_name account, string &avatar, string &full_image, string &website, string &facebook,
				 string &twitter, string &medium, string &steemit, string &telegram, string &github,
				 string &organization);

	//@abi action
	void create(account_name issuer,
				asset maximum_supply);

	//@abi action
	void rentareas(account_name renter, vector<uint64_t> areas);

	//@abi action
	void buyarea(account_name buyer, uint64_t price_per_square);

	//@abi action
	void payplant(uint64_t area, account_name payer, account_name renter);

	//@abi action
	void paywater(uint64_t area, account_name payer, account_name renter);

};


#endif //EOSIO_global_square_HPP
