/*
 * Copyright (c) 2018-2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <switch.h>
#include <stratosphere.hpp>

#include "spl_types.hpp"

class SmcWrapper {
    public:
        static inline u32 GetCryptAesMode(SmcCipherMode mode, u32 keyslot) {
            return static_cast<u32>((mode << 4) | (keyslot & 7));
        }
        static inline u32 GetUnwrapEsKeyOption(EsKeyType type, u32 generation) {
            return static_cast<u32>((type << 6) | (generation & 0x3F));
        }
    public:
        static SmcResult SetConfig(SplConfigItem which, const u64 *value, size_t num_qwords);
        static SmcResult GetConfig(u64 *out, size_t num_qwords, SplConfigItem which);
        static SmcResult CheckStatus(SmcResult *out, AsyncOperationKey op);
        static SmcResult GetResult(SmcResult *out, void *out_buf, size_t out_buf_size, AsyncOperationKey op);
        static SmcResult ExpMod(AsyncOperationKey *out_op, const void *base, const void *exp, size_t exp_size, const void *mod);
        static SmcResult GenerateRandomBytes(void *out, size_t size);
        static SmcResult GenerateAesKek(AccessKey *out, const KeySource &source, u32 generation, u32 option);
        static SmcResult LoadAesKey(u32 keyslot, const AccessKey &access_key, const KeySource &source);
        static SmcResult CryptAes(AsyncOperationKey *out_op, u32 mode, const IvCtr &iv_ctr, u32 dst_addr, u32 src_addr, size_t size);
        static SmcResult GenerateSpecificAesKey(AesKey *out_key, const KeySource &source, u32 generation, u32 which);
        static SmcResult ComputeCmac(Cmac *out_mac, u32 keyslot, const void *data, size_t size);
        static SmcResult ReEncryptRsaPrivateKey(void *data, size_t size, const AccessKey &access_key_dec, const KeySource &source_dec, const AccessKey &access_key_enc, const KeySource &source_enc, u32 option);
        static SmcResult DecryptOrImportRsaPrivateKey(void *data, size_t size, const AccessKey &access_key, const KeySource &source, u32 option);
        static SmcResult SecureExpMod(AsyncOperationKey *out_op, const void *base, const void *mod, u32 option);
        static SmcResult UnwrapTitleKey(AsyncOperationKey *out_op, const void *base, const void *mod, const void *label_digest, size_t label_digest_size, u32 option);
        static SmcResult LoadTitleKey(u32 keyslot, const AccessKey &access_key);
        static SmcResult UnwrapCommonTitleKey(AccessKey *out, const KeySource &source, u32 generation);

        /* Deprecated functions. */
        static SmcResult ImportEsKey(const void *data, size_t size, const AccessKey &access_key, const KeySource &source, u32 option);
        static SmcResult DecryptRsaPrivateKey(size_t *out_size, void *data, size_t size, const AccessKey &access_key, const KeySource &source, u32 option);
        static SmcResult ImportSecureExpModKey(const void *data, size_t size, const AccessKey &access_key, const KeySource &source, u32 option);
};
