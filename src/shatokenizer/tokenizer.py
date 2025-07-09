# tokenizer_ext.py
import json
from .shatokenizer import ShaTokenizerAPI

class ShaTokenizer(ShaTokenizerAPI):
    def save(self, path: str):
        with open(path, "w") as f:
            json.dump({
                "vocab_size":     self.vocab_size,
                "bpe_ranks":      {f"{k[0]} {k[1]}": v for k, v in self.bpe_rank.items()},
                "token_to_id":    dict(self.token_to_id),
                "id_to_token":    {str(k): v for k, v in self.id_to_token.items()},
                "special_tokens": {
                    "pad":   self.get_pad_id(),
                    "unk":   self.get_unk_id(),
                    "start": self.get_start_id(),
                    "end":   self.get_end_id()
                },
                "vocab":          self.vocab  # string -> int
            }, f, indent=2)
    def load(self, path: str):
        with open(path, "r") as f:
            data = json.load(f)
        self.vocab_size     = data["vocab_size"]
        self.bpe_rank       = {tuple(k.split()): v for k, v in data["bpe_ranks"].items()}
        self.token_to_id    = {k: int(v) for k, v in data["token_to_id"].items()}
        self.id_to_token    = {int(k): v for k, v in data["id_to_token"].items()}
        self.pad_token_id   = data["special_tokens"]["pad"]
        self.unk_token_id   = data["special_tokens"]["unk"]
        self.start_token_id = data["special_tokens"]["start"]
        self.end_token_id   = data["special_tokens"]["end"]
        self.vocab          = data["vocab"]
